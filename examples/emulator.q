@encoding utf8
@lang v1
@author Wesley Jones
@license CC0/Public Domain
@signature TWgLVxZHvcMO5wTzJgZBcbcXJbHgjV838ZoRRdLfIfDppjuWtk5UZv6cuXeqFTAVAqNsBoxgje4LCU9p7URz0bHDsvlVZ5OIV15JdJINjYS7QnsbHV3KnyBlhYkEPrkgt
@date 2024-03-05
@clevel all extra pedantic

import proc;
import sysio;
import runtime;
import quixcc;

@define STATE_SAV_PATH "~/ionlang-emulator.state"

@(orbitsafey(                                                                              ~> Check if each component of the standand library is properly
                                                                                           ~> initialied before it is referenced

pub impure tsafe fn _start() {                                                             ~> Define a public, impure, thread-safe function named _start
    const [argc: i32, argv: [string]] = undef;                                             ~> Create an undefined, one-time-assignable, coupled constant
    const file: string = undef;                                                            ~> Create an undefined, one-time-assignable constant
    const code: quixcc::Code = undef;                                                      ~> Create an undefined, one-time-assignable constant
    const [mstate: runtime::MachineState] = undef;                                         ~> Create an undefined, one-time-assignable, coupled constant
    const e: stat = undef;                                                                 ~> Create an undefined, one-time-assignable constant

    abortif !proc.init() || !sysio.stdstream() || !sysio.fs();                             ~> Initialize core subsystems
    abortif !runtime.init();                                                               ~> Initialize runtime components

    [argc, argv] = proc::options();                                                        ~> Get command line options
    retif 1, argc < 2, () => writeln("Usage: {argv[0]} [file]");                           ~> Check for file argument

    retif 2, !sysio::exists(file = argv[1]), () => writeln("File not found: {file}");      ~> Check if file exists
    retif 3, [code, e] = quixcc::compile(file); e, ()=>writeln("Compilation failed: {e}"); ~> Compile the source into bytecode

    mstate = runtime::emulate(code);                                                       ~> Emulate the compiled code
    
    writeln("Emulation result: {mstate.dumpregs()}");                                      ~> Print register dump
    retif 4, !mstate.savefile(STATE_SAV_PATH, code), () => writeln("Filed to save state"); ~> Save emulator state to file
    
    proc.exit(0);                                                                          ~> Exit process with status 0 (OK)
}

))