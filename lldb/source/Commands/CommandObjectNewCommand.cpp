//===-- CommandObjectNewCommand.cpp --------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "CommandObjectNewCommand.h"
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


class CommandObjectMyCommandTalha : public CommandObjectParsed {
  public:
    CommandObjectMyCommandTalha(CommandInterpreter &interpreter)
        : CommandObjectParsed(interpreter, "mycommand",
                              "Print My name is talha",
                              nullptr){}
    ~CommandObjectMyCommandTalha() override = default;
  protected:
    bool DoExecute(Args &command, CommandReturnObject &result) override {
    // printf("Inside the Execute of the command\n");
    result.AppendMessage("My name is talha");
    result.SetStatus(eReturnStatusSuccessFinishResult);
    return result.Succeeded();
  }
};

// CommandObjectNewCommand

CommandObjectNewCommand::CommandObjectNewCommand(
    CommandInterpreter &interpreter)
    : CommandObjectMultiword(
          interpreter, "hello",
          "Commands for printing my name",
          "breakpoint hello mycommand") {

  CommandObjectSP talha_command_object(
      new CommandObjectMyCommandTalha(interpreter));

  talha_command_object->SetCommandName("breakpoint hello mycommand");

  LoadSubCommand("mycommand", talha_command_object);
}

CommandObjectNewCommand::~CommandObjectNewCommand() = default;
