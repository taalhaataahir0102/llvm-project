//===-- CommandObjectHi.cpp --------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "CommandObjectHi.h"
#include "CommandObjectBreakpoint.h"
#include "lldb/Breakpoint/Breakpoint.h"
#include "lldb/Breakpoint/BreakpointIDList.h"
#include "lldb/Breakpoint/BreakpointLocation.h"
#include "lldb/Core/IOHandler.h"
#include "lldb/Host/OptionParser.h"
#include "lldb/Interpreter/CommandInterpreter.h"
#include "lldb/Interpreter/CommandOptionArgumentTable.h"
#include "lldb/Interpreter/CommandReturnObject.h"
#include "lldb/Interpreter/OptionArgParser.h"
#include "lldb/Interpreter/OptionGroupPythonClassWithDict.h"
#include "lldb/Target/Target.h"
#include <stdio.h>

using namespace lldb;
using namespace lldb_private;

class CommandObjectHiExecute : public CommandObjectParsed {
public:
  CommandObjectHiExecute(CommandInterpreter &interpreter)
      : CommandObjectParsed(
            interpreter, "hi",
            "Print the word n number of times.",
            "breakpoint hi <word> <number>") {}

  ~CommandObjectHiExecute() override = default;

protected:
  bool DoExecute(Args &command, CommandReturnObject &result) override {
    printf("Inside the DoExecute\n");
    printf("command.GetArgumentCount(): %ld\n", command.GetArgumentCount());
    if (command.GetArgumentCount() != 2) {
      result.AppendErrorWithFormat("Invalid number of arguments; expected 'hi <word> <number>'.\n");
      result.SetStatus(eReturnStatusFailed);
      return false;
    }

    const char *word = command.GetArgumentAtIndex(0);
    const char *number_str = command.GetArgumentAtIndex(1);
    uint64_t number;
    if (!llvm::to_integer(number_str, number)) {
      result.AppendErrorWithFormat("Invalid number argument '%s'; expected a positive integer.\n", number_str);
      result.SetStatus(eReturnStatusFailed);
      return false;
    }

    for (uint64_t i = 0; i < number; ++i) {
      result.AppendMessage(word);
    }

    result.SetStatus(eReturnStatusSuccessFinishResult);
    return true;
  }
};

// CommandObjectHi

CommandObjectHi::CommandObjectHi(CommandInterpreter &interpreter)
    : CommandObjectMultiword(
          interpreter, "hi",
          "Print the word n number of times.",
          "breakpoint hi <word> <number>") {

  CommandObjectSP hi_command_object(new CommandObjectHiExecute(interpreter));

  LoadSubCommand("hi", hi_command_object);
}

CommandObjectHi::~CommandObjectHi() = default;
