# Debagovanje

| Interpreter                 | Just-In-Time (JIT)                 | Ahead-Of-Time (AOT)             |
|-----------------------------|------------------------------------|---------------------------------|
| interpretation              | interpretation + compilation       | compilation (and optimization!) |
| quick development feedback  | quick development feedback         | slow development feedback       |
| executes only some paths    | compilation to intermediate format | full compilation/optimization   |
| (runtime errors)            | + runtime compilation/optimization |                                 |
| portable code               | portable code                      | limited portability             |
| slow startup                | slow startup                       | fast startup                    |
| slow peak performance       | highest peak performance           | high(est?) peak performance     |
| easy to profile             | easy to profile (builtin)          | hard to profile                 |
| easy to instrument          | relatively easy to instrument      | hard to instrument              |
| dynamic features            | dynamic features                   | usually no dynamic features     |
| highest memory footprint    | high memory footprint              | low memory footprint            |
| runtime required            | runtime required                   | no runtime required             | 
|                             |                                    | (e.g., static compilation)      |

