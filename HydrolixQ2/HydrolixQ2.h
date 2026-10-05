// HydrolixQ2.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <memory>
#include <cassert>

#define TEST_ASSERT(condition, success_msg, error_msg) \
    do { \
        if (condition) { \
            std::cout << "[SUCCESS] " << success_msg << "\n"; \
        } else { \
            std::cerr << "[FAILURE] " << __FILE__ << ":" << __LINE__ \
                      << " - " << error_msg << "\n"; \
            std::abort(); \
        } \
    } while (0)


// ========= Helper Code =========
class DataType;
using DataTypePtr = std::shared_ptr<DataType>;

// Please handle these type families ("kinds"):
enum DataTypeKind { nullable, int64, array, string };

// This class holds all necessary information about a column's datatype.
class DataType {
public:
	explicit DataType(DataTypeKind kind, DataTypePtr subtype = {} /*defaults to an empty*/)
		: _kind(kind),
		_subtype(std::move(subtype)) {};
	[[nodiscard]] auto kind() const { return _kind; }
	[[nodiscard]] auto subtype() const { return _subtype; }
private:
	DataTypeKind _kind;
	DataTypePtr _subtype;
};

// ========= The function we'd like you to write: =========
static bool
trivially_convertible(const DataTypePtr& from_type, const DataTypePtr& to_type) {
	if (!from_type || !to_type) return false;
	// Validation for missing subtypes: return false if a composite type lacks a subtype.
	// This helps to verify fast-fail behavior, courtesy: GitHub co-pilot
	auto ensure_subtype = [](const DataTypePtr& t) -> bool {
		if (t->kind() == DataTypeKind::array || t->kind() == DataTypeKind::nullable)
			return static_cast<bool>(t->subtype());
		return true;
	};
	if (!ensure_subtype(from_type) || !ensure_subtype(to_type)) return false;

	const bool from_nullable = from_type->kind() == DataTypeKind::nullable;
	const bool to_nullable = to_type->kind() == DataTypeKind::nullable;

	// Nullable -> non-Nullable needs a replacement value for NULLs: not trivial.
	if (from_nullable && !to_nullable) return false;

	// Target is Nullable: strip its wrapper (and the source's, if present)
	// and compare the underlying types. Non-Nullable -> Nullable is trivial
	// as long as the base types are.
	if (to_nullable) {
		return trivially_convertible(from_nullable ? from_type->subtype() : from_type,
			to_type->subtype());
	}

	// Neither side is Nullable at this level.
	if (from_type->kind() != to_type->kind()) return false;

	// At this stage - to_type->kind() is also == array so checking for one 
	if (from_type->kind() == DataTypeKind::array) {
		// Element types may gain Nullable wrappers at any depth.
		return trivially_convertible(from_type->subtype(), to_type->subtype());
	}

	// Same leaf kind (int64 / string).
	return true;
}

