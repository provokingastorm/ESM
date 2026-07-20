## User Story
****
As a developer, I can run and debug ESM through Visual Studio 2016. 

## Acceptance Criteria
****
 - I am can run CMake on the ESM project while yielding no errors in the console output.
 - I am able to run the outputted Visual Studio solution without any new errors or warnings.
 - All batch scripts that don't successfully run on previous revisions of Visual Studio are removed from the depot.

## Status Report
****


## Next Actions
****
- [ ] Create a `cmake_studio2026.bat` script to kick off CMake for Visual Studio 2026.
- [ ] Update all of the CMake build scripts require a minimum of 4.2.
- [ ] Move all instances of `cmake_minimum_required()` to the front of the script (`project()` comes after).
- [ ] Change all instances of the legacy `include_directories()` to `target_include_directories()`.
- [ ] Change all instances of the legacy `link_libraries()` to `target_link_libraries()`.
- [ ] Change all instances of the legacy `link_directories()` to `target_link_directories()`.

## Before Submission Tasks
****
- [ ] 

## Investigation Tasks
****
- [ ] 

## Deferred Actions
****
- [ ] 

## Experiments
****


## Documents
****


## Links
****
- 

## Notes
****
 - 

**Batch Script for CMake Visual Studio 2026**
`@echo off
mkdir _build
cd _build
"../cmake/bin/cmake.exe" -A Win32 -G "Visual Studio 18 2026" ..
`

## Finished Tasks
****
