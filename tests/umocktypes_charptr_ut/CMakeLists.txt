#Copyright (c) Microsoft. All rights reserved.
#Licensed under the MIT license. See LICENSE file in the project root for full license information.

set(theseTestsName umocktypes_charptr_ut)

set(${theseTestsName}_test_files
umocktypes_charptr_ut.c
)

set(${theseTestsName}_c_files
umocktypes_charptr_mocked.c
)

set(${theseTestsName}_h_files
)

build_test_artifacts(${theseTestsName} "tests/umockc_tests")
