//===-- core/Engine.cpp - C++ wrapper over the WSTP/MathLink API ----------===//
//
// Copyright (c) 2021 Jon Palmisciano; licensed under the BSD 3-Clause license.
//
// This file is part of AMU, an open source UI for the Wolfram Engine. The
// source code for AMU is available at <https://github.com/jonpalmisc/amu>.
//
//===----------------------------------------------------------------------===//

#include <amu/Engine.h>

namespace amu {

Engine::Engine()
    : m_env(nullptr)
    , m_link(nullptr)
{
}

Error Engine::init(const std::string& kernelPath)
{
    m_env = WSInitialize(nullptr);
    if (!m_env) {
        return Error::BadEnvironment;
    }

    int error = 0;
    const char* args[] = { "Amu", "-linkname", kernelPath.c_str(), "-linkmode", "launch" };
    m_link = WSOpenArgcArgv(m_env, 5, (char**)args, &error);
    if (!m_link) {
        WSDeinitialize(m_env);
        return Error::BadLink;
    }

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

std::string Engine::eval(const std::string& input) const
{
    int resultSize, _;
    const unsigned char* resultBytes;

    WSPutFunction(m_link, "EvaluatePacket", 1);
    WSPutFunction(m_link, "ToString", 1);
    WSPutFunction(m_link, "ToExpression", 1);
    WSPutString(m_link, input.c_str());
    WSEndPacket(m_link);

    // Wait for return packet.
    while (WSNextPacket(m_link) != RETURNPKT)
        WSNewPacket(m_link);

    // Get the result buffer and create a C++ string from it.
    WSGetUTF8String(m_link, &resultBytes, &resultSize, &_);
    std::string result(resultBytes, resultBytes + resultSize);

    // Free the raw buffer and return the C++ string.
    WSReleaseUTF8String(m_link, resultBytes, resultSize);
    return result;
}

}
