//===-- include/amu/Engine.h - C++ wrapper over the WSTP/MathLink API -----===//
//
// Copyright (c) 2021 Jon Palmisciano; licensed under the BSD 3-Clause license.
//
// This file is part of AMU, an open source UI for the Wolfram Engine. The
// source code for AMU is available at <https://github.com/jonpalmisc/amu>.
//
//===----------------------------------------------------------------------===//

#pragma once

#include <wstp.h>

#include <string>

namespace amu {

/// Engine error type.
enum class Error {
    None,
    BadEnvironment,
    BadLink,
};

/// C++ wrapper enum for packet type constants.
enum class PacketType : int {
    Illegal = ILLEGALPKT,
    Suspend = SUSPENDPKT,

    Input = INPUTPKT,
    ReturnText = RETURNTEXTPKT,

    InputName = INPUTNAMEPKT,
    OutputName = OUTPUTNAMEPKT,
};

/// A wrapper over a Wolfram Engine link and environment.
class Engine {
    WSENV m_env;
    WSLINK m_link;

    bool m_isInitialized;
    int m_lastOutputId;
    int m_nextInputId;

public:
    Engine();

    /// Initialize the link with the given parameters.
    ///
    /// \param params Path to the Wolfram Kernel to use
    Error init(const std::string& kernelPath);

    /// Shut down the underlying engine and link.
    void deinit();

    /// Evaluate the given input with the engine.
    ///
    /// \param input The input (Wolfram Language) to evaluate
    std::string eval(const std::string& input);

    /// Get the last output cell ID returned from the engine.
    int lastOutputId() const { return m_lastOutputId; }

    /// Get the ID for the next input cell (as instructed by the engine).
    int nextInputId() const { return m_nextInputId; }
};

}
