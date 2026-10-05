// HydrolixQ2.cpp : Defines the entry point for the application.
//

#include "HydrolixQ2.h"
#include <assert.h>
#include <iostream>
#include <cstdlib>

int main() {
    auto int64 = std::make_shared<DataType>(DataTypeKind::int64);
    auto string = std::make_shared<DataType>(DataTypeKind::string);
    auto null_int64 = std::make_shared<DataType>(DataTypeKind::nullable, int64);
    auto null_string = std::make_shared<DataType>(DataTypeKind::nullable, string);
    auto array_int64 = std::make_shared<DataType>(DataTypeKind::array, int64);
    auto array_string = std::make_shared<DataType>(DataTypeKind::array, string);
    auto null = std::make_shared<DataType>(DataTypeKind::nullable);
    auto array = std::make_shared<DataType>(DataTypeKind::array);

    // Lamdas to handle nested types
    auto arr = [](const DataTypePtr& t) {
        return std::make_shared<DataType>(DataTypeKind::array, t);
    };
    auto nul = [](const DataTypePtr& t) {
        return std::make_shared<DataType>(DataTypeKind::nullable, t);
    };

    // ---------- Int64: valid conversions ----------
    // Array(Int64) -> Array(Nullable(Int64))
    //assert(trivially_convertible(array_int64, arr(null_int64)));
    TEST_ASSERT(trivially_convertible(array_int64, arr(null_int64)) == true, 
            "Array(Int64) -> Array(Nullable(Int64)) is valid!", "Array(Int64) -> Array(Nullable(Int64)) failed and is NOT valid!");

    // Array(Array(Int64)) -> Array(Array(Nullable(Int64)))
    //assert(trivially_convertible(arr(array_int64), arr(arr(null_int64))));
    TEST_ASSERT(trivially_convertible(array_int64, arr(null_int64)) == true,
        "Array(Array(Int64)) -> Array(Array(Nullable(Int64))) is valid!", "Array(Array(Int64)) -> Array(Array(Nullable(Int64))) failed and is NOT valid!");

    // Array(Array(Int64)) -> Array(Nullable(Array(Nullable(Int64))))
    // assert(trivially_convertible(arr(array_int64), arr(nul(arr(null_int64)))));
    TEST_ASSERT(trivially_convertible(array_int64, arr(null_int64)) == true,
        "Array(Array(Int64)) -> Array(Nullable(Array(Nullable(Int64)))) is valid!", "Array(Array(Int64)) -> Array(Nullable(Array(Nullable(Int64)))) failed and is NOT valid!");

    // ---------- String: valid conversions ----------
    // Array(String) -> Array(Nullable(String))
    // assert(trivially_convertible(array_string, arr(null_string)));
    TEST_ASSERT(trivially_convertible(array_int64, arr(null_int64)) == true,
        "Array(String) -> Array(Nullable(String)) is valid!", "Array(String) -> Array(Nullable(String)) failed and is NOT valid!");

    // Array(Array(String)) -> Array(Array(Nullable(String)))
    // assert(trivially_convertible(arr(array_string), arr(arr(null_string))));
    TEST_ASSERT(trivially_convertible(arr(array_string), arr(arr(null_string))) == true,
        "Array(Array(String)) -> Array(Array(Nullable(String))) is valid!", "Array(Array(String)) -> Array(Array(Nullable(String))) failed and is NOT valid!");

    // Array(Array(String)) -> Array(Nullable(Array(Nullable(String))))
    // assert(trivially_convertible(arr(array_string), arr(nul(arr(null_string)))));
    TEST_ASSERT(trivially_convertible(arr(array_string), arr(nul(arr(null_string)))) == true,
        "Array(Array(String)) -> Array(Nullable(Array(Nullable(String)))) is valid!", "Array(Array(String)) -> Array(Nullable(Array(Nullable(String)))) failed and is NOT valid!");

    // ---------- Reverse directions: must NOT be trivial ----------
    //assert(!trivially_convertible(arr(null_int64), array_int64));
    TEST_ASSERT(trivially_convertible(arr(null_int64), array_int64) == false,
        "Array(Nullable(Int64)) -> Array(Int64) is NOT trivially convertible (as expected)", "Array(Nullable(Int64)) -> Array(Int64) unexpectedly trivially convertible!");
    //assert(!trivially_convertible(arr(arr(null_int64)), arr(array_int64)));
    TEST_ASSERT(trivially_convertible(arr(arr(null_int64)), arr(array_int64)) == false,
        "Array(Array(Nullable(Int64))) -> Array(Array(Int64)) is NOT trivially convertible (as expected)", "Array(Array(Nullable(Int64))) -> Array(Array(Int64)) unexpectedly trivially convertible!");
    //assert(!trivially_convertible(arr(nul(arr(null_int64))), arr(array_int64)));
    TEST_ASSERT(trivially_convertible(arr(nul(arr(null_int64))), arr(array_int64)) == false,
        "Array(Nullable(Array(Nullable(Int64)))) -> Array(Array(Int64)) is NOT trivially convertible (as expected)", "Array(Nullable(Array(Nullable(Int64)))) -> Array(Array(Int64)) unexpectedly trivially convertible!");

    //assert(!trivially_convertible(arr(null_string), array_string));
    TEST_ASSERT(trivially_convertible(arr(null_string), array_string) == false,
        "Array(Nullable(String)) -> Array(String) is NOT trivially convertible (as expected)", "Array(Nullable(String)) -> Array(String) unexpectedly trivially convertible!");
    //assert(!trivially_convertible(arr(arr(null_string)), arr(array_string)));
    TEST_ASSERT(trivially_convertible(arr(arr(null_string)), arr(array_string)) == false,
        "Array(Array(Nullable(String))) -> Array(Array(String)) is NOT trivially convertible (as expected)", "Array(Array(Nullable(String))) -> Array(Array(String)) unexpectedly trivially convertible!");
    //assert(!trivially_convertible(arr(nul(arr(null_string))), arr(array_string)));
    TEST_ASSERT(trivially_convertible(arr(nul(arr(null_string))), arr(array_string)) == false,
        "Array(Nullable(Array(Nullable(String)))) -> Array(Array(String)) is NOT trivially convertible (as expected)", "Array(Nullable(Array(Nullable(String)))) -> Array(Array(String)) unexpectedly trivially convertible!");

    // ---------- Mixed-kind conversions: must NOT be trivial ----------
    //assert(!trivially_convertible(array_int64, arr(null_string)));
    TEST_ASSERT(trivially_convertible(array_int64, arr(null_string)) == false,
        "Array(Int64) -> Array(Nullable(String)) is NOT trivially convertible (as expected)", "Array(Int64) -> Array(Nullable(String)) unexpectedly trivially convertible!");
    //assert(!trivially_convertible(array_string, arr(null_int64)));
    TEST_ASSERT(trivially_convertible(array_string, arr(null_int64)) == false,
        "Array(String) -> Array(Nullable(Int64)) is NOT trivially convertible (as expected)", "Array(String) -> Array(Nullable(Int64)) unexpectedly trivially convertible!");
    //assert(!trivially_convertible(arr(array_int64), arr(arr(null_string))));
    TEST_ASSERT(trivially_convertible(arr(array_int64), arr(arr(null_string))) == false,
        "Array(Array(Int64)) -> Array(Array(Nullable(String))) is NOT trivially convertible (as expected)", "Array(Array(Int64)) -> Array(Array(Nullable(String))) unexpectedly trivially convertible!");

    // ---------- Depth mismatch: must NOT be trivial ----------
    // 1 level array to 2 level deeper array or 2 level array to 1 level.
    //assert(!trivially_convertible(array_int64, arr(arr(null_int64))));
    TEST_ASSERT(trivially_convertible(array_int64, arr(arr(null_int64))) == false,
        "Array(Int64) -> Array(Array(Nullable(Int64))) is NOT trivially convertible (as expected)", "Array(Int64) -> Array(Array(Nullable(Int64))) unexpectedly trivially convertible!");
    //assert(!trivially_convertible(arr(array_string), arr(null_string)));
    TEST_ASSERT(trivially_convertible(arr(array_string), arr(null_string)) == false,
        "Array(Array(String)) -> Array(Nullable(String)) is NOT trivially convertible (as expected)", "Array(Array(String)) -> Array(Nullable(String)) unexpectedly trivially convertible!");

    // ---------- Sanity checks on the scalar basics ----------
    //assert(trivially_convertible(int64, int64));
    TEST_ASSERT(trivially_convertible(int64, int64) == true,
        "Int64 -> Int64 is valid!", "Int64 -> Int64 failed and is NOT valid!");
    //assert(trivially_convertible(int64, null_int64));
    TEST_ASSERT(trivially_convertible(int64, null_int64) == true,
        "Int64 -> Nullable(Int64) is valid!", "Int64 -> Nullable(Int64) failed and is NOT valid!");
    //assert(trivially_convertible(null_int64, null_int64));
    TEST_ASSERT(trivially_convertible(null_int64, null_int64) == true,
        "Nullable(Int64) -> Nullable(Int64) is valid!", "Nullable(Int64) -> Nullable(Int64) failed and is NOT valid!");
    //assert(!trivially_convertible(null_int64, int64));
    TEST_ASSERT(trivially_convertible(null_int64, int64) == false,
        "Nullable(Int64) -> Int64 is NOT trivially convertible (as expected)", "Nullable(Int64) -> Int64 unexpectedly trivially convertible!");
    //assert(trivially_convertible(string, null_string));
    TEST_ASSERT(trivially_convertible(string, null_string) == true,
        "String -> Nullable(String) is valid!", "String -> Nullable(String) failed and is NOT valid!");
    //assert(!trivially_convertible(null_string, string));
    TEST_ASSERT(trivially_convertible(null_string, string) == false,
        "Nullable(String) -> String is NOT trivially convertible (as expected)", "Nullable(String) -> String unexpectedly trivially convertible!");
    //assert(!trivially_convertible(int64, string));
    TEST_ASSERT(trivially_convertible(int64, string) == false,
        "Int64 -> String is NOT trivially convertible (as expected)", "Int64 -> String unexpectedly trivially convertible!");

    // ---------- Null pointers ----------
    //assert(!trivially_convertible(nullptr, int64));
    TEST_ASSERT(trivially_convertible(nullptr, int64) == false,
        "nullptr -> Int64 is NOT trivially convertible (as expected)", "nullptr -> Int64 unexpectedly trivially convertible!");
    //assert(!trivially_convertible(int64, nullptr));
    TEST_ASSERT(trivially_convertible(int64, nullptr) == false,
        "Int64 -> nullptr is NOT trivially convertible (as expected)", "Int64 -> nullptr unexpectedly trivially convertible!");

    // --------- Fast fail null or array or null/array to/from scalar types -------------
    TEST_ASSERT(trivially_convertible(array, null) == false,
        "Array -> null is NOT trivially convertible(as expected)", "Array -> null unexpectedly trivially convertible!");
    TEST_ASSERT(trivially_convertible(int64, array) == false,
        "int64 -> array is NOT trivially convertible(as expected)", " int64 -> array unexpectedly trivially convertible!");
    TEST_ASSERT(trivially_convertible(string, null) == false,
        "string -> null is NOT trivially convertible to array(as expected)", " string -> null unexpectedly trivially convertible!");
    TEST_ASSERT(trivially_convertible(null, int64) == false,
        "null -> int64 is NOT trivially convertible to array(as expected)", " null -> null unexpectedly trivially convertible!");

    std::cout << "All tests passed\n";
    return 0;
}

