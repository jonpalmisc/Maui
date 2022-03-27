//===-- core/Engine.cpp - C++ wrapper over the WSTP/MathLink API ----------===//
//
// Copyright (c) 2021 Jon Palmisciano; licensed under the BSD 3-Clause license.
//
// This file is part of Maui, an open source UI for the Wolfram Engine. The
// source code for Maui is available at <https://github.com/jonpalmisc/Maui>.
//
//===----------------------------------------------------------------------===//

#include <maui/Engine.h>
#include <maui/Tools.h>

#include <iostream>

namespace maui {

Engine::Engine()
    : m_env(nullptr)
    , m_link(nullptr)
    , m_lastOutputId(0)
    , m_nextInputId(1)
{
}

Error Engine::init(const std::string& kernelPath)
{
    m_env = WSInitialize(nullptr);
    if (!m_env) {
        return Error::BadEnvironment;
    }

    int error = 0;
    const char* args[] = { "Maui", "-linkname", kernelPath.c_str(), "-linkmode", "launch" };
    m_link = WSOpenArgcArgv(m_env, 5, (char**)args, &error);
    if (!m_link) {
        WSDeinitialize(m_env);
        return Error::BadLink;
    }

    // Recieve and ignore the first input name packet. This "aligns" the packet
    // cycle so that `eval` works smoothly.
    WSNextPacket(m_link);
    WSNewPacket(m_link);

    m_isInitialized = true;
    return Error::None;
}

void Engine::deinit()
{
    // Nothing to be done if initialization failed.
    if (!m_isInitialized)
        return;

    WSClose(m_link);
    WSDeinitialize(m_env);
}

std::string Engine::eval(const std::string& input)
{
    WSPutFunction(m_link, "EnterTextPacket", 1);
    WSPutString(m_link, input.c_str());
    WSEndPacket(m_link);

    PacketType packetType;
    const char* rawResult;
    std::string result;

    bool done = false;
    while (!done) {
        packetType = (PacketType)WSNextPacket(m_link);
        switch (packetType) {
        case PacketType::ReturnText:
            if (WSGetString(m_link, &rawResult)) {
                // This is a hack to display the error strings without a major refactor.
                // When there is an error, the result will already be containing the
                // error string. However, the engine will still somehow give a result.
                // For example, if we evaluate 1/0, we will get an error message,
                // followed by ComplexInfinity as its result
                //				                                 1
                //                Power::infy: Infinite expression - encountered.
                //                                                 0
                //
                //                ComplexInfinity
                if (!result.empty())
                    result += std::string("\n\n") + std::string(rawResult);
                else
                    result = std::string(rawResult);
                WSReleaseString(m_link, rawResult);
            }

            break;

        case PacketType::OutputName:
            if (WSGetString(m_link, &rawResult)) {
                m_lastOutputId = extractId(rawResult);
                WSReleaseString(m_link, rawResult);
            }

            break;

        // These types of packets can effectively be treated as a signal that
        // this communication cycle is over. There will be no more packets to
        // handle after one of these is recieved.
        case PacketType::InputName:
            if (WSGetString(m_link, &rawResult)) {
                m_nextInputId = extractId(rawResult);
                WSReleaseString(m_link, rawResult);
            }
        case PacketType::Input:
        case PacketType::Suspend:
            done = true;
            break;

            //		When there is an error, we will receive a MESSAGEPKT followed by TEXTPKT.
            //		The MESSAGEPKT will contain a symbol and a message. For example, if the
            //		error is the following,
            //		Increment::rvalue:
            //		   1 is not a variable with a value, so its value cannot be changed.

            //		The symbol will be "Increment", and the message will be "rvalue".
            //		The text message will be the entire error message (including the Increment::rvalue:
            //		on the first line).
            //		Since we only need to display the error message, we ignore the MESSAGEPKT
        case PacketType::Message: {
            //		    const char *symbol;
            //            if (WSGetSymbol(m_link, &symbol))
            //			{
            //				result += std::string(symbol);
            //				WSReleaseSymbol(m_link, symbol);
            //			}
            //			if (WSGetString(m_link, &rawResult)) {
            //				result += std::string(rawResult);
            //				WSReleaseString(m_link, rawResult);
            //			}
            break;
        }

        case PacketType::Text: {
            if (WSGetString(m_link, &rawResult)) {
                result += std::string(rawResult);
                WSReleaseString(m_link, rawResult);
            }
            break;
        }

        // Not sure what produces illegal packets, but maybe their existence
        // should be logged if one is received.
        // Illegal packets are encountered when the engine is not activated
        case PacketType::Illegal: {
            std::cerr << "Warning: Recieved illegal packet" << std::endl;
            std::string error = WSErrorMessage(m_link);
            if (!error.empty())
                std::cerr << "Error: " << error << std::endl;

            if (!WSClearError(m_link) || !WSNewPacket(m_link))
                done = true;

            break;
        }

        // There are a handful of packets that can be safely ignored, but for
        // now they should all be logged for development purposes.
        default:
            std::cerr << "Warning: Unhandled type " << (int)packetType << " packet\n";
            break;
        }

        WSNewPacket(m_link);
    }

    return octalUnescape(result);
}

std::string Engine::evalRaw(const std::string& input)
{
    WSPutFunction(m_link, "EvaluatePacket", 1);
    WSPutFunction(m_link, "ToExpression", 1);
    WSPutString(m_link, input.c_str());
    WSEndPacket(m_link);

    const char* rawResult;
    std::string result;
    PacketType packetType = (PacketType)WSNextPacket(m_link);
    if (packetType != PacketType::Return)
        return "";

    if (WSGetString(m_link, &rawResult)) {
        result = std::string(rawResult);
        WSReleaseString(m_link, rawResult);
    }

    return octalUnescape(result);
}

}
