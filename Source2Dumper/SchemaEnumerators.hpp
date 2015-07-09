#pragma once

// obtained by parsing the schema enumerator list :)

enum SchemaClassFlags_t
{
	SCHEMA_CLASS_HAS_VIRTUAL_MEMBERS = 1,
	SCHEMA_CLASS_IS_ABSTRACT = 2,
	SCHEMA_CLASS_HAS_TRIVIAL_CONSTRUCTOR = 4,
	SCHEMA_CLASS_HAS_TRIVIAL_DESTRUCTOR = 8,
	SCHEMA_CLASS_TEMP_HACK_HAS_NOSCHEMA_MEMBERS = 16,
	SCHEMA_CLASS_TEMP_HACK_HAS_CONSTRUCTOR_LIKE_METHODS = 32,
	SCHEMA_CLASS_TEMP_HACK_HAS_DESTRUCTOR_LIKE_METHODS = 64,
	SCHEMA_CLASS_IS_NOSCHEMA_CLASS = 128,
};

enum SchemaFieldType_t
{
	SCHEMA_FIELD_TYPE_UNKNOWN = 0,
	SCHEMA_FIELD_TYPE_STRUCT = 1,
	SCHEMA_FIELD_TYPE_ENUM = 2,
	SCHEMA_FIELD_TYPE_EXT_REFERENCE = 3,
	SCHEMA_FIELD_TYPE_CHAR = 4,
	SCHEMA_FIELD_TYPE_UCHAR = 5,
	SCHEMA_FIELD_TYPE_INT = 6,
	SCHEMA_FIELD_TYPE_UINT = 7,
	SCHEMA_FIELD_TYPE_FLOAT = 8,
	SCHEMA_FIELD_TYPE_DOUBLE = 9,
	SCHEMA_FIELD_TYPE_INT8 = 10,
	SCHEMA_FIELD_TYPE_UINT8 = 11,
	SCHEMA_FIELD_TYPE_INT16 = 12,
	SCHEMA_FIELD_TYPE_UINT16 = 13,
	SCHEMA_FIELD_TYPE_INT32 = 14,
	SCHEMA_FIELD_TYPE_UINT32 = 15,
	SCHEMA_FIELD_TYPE_INT64 = 16,
	SCHEMA_FIELD_TYPE_UINT64 = 17,
	SCHEMA_FIELD_TYPE_FLOAT32 = 18,
	SCHEMA_FIELD_TYPE_FLOAT64 = 19,
	SCHEMA_FIELD_TYPE_TIME = 20,
	SCHEMA_FIELD_TYPE_VECTOR2D = 21,
	SCHEMA_FIELD_TYPE_VECTOR3D = 22,
	SCHEMA_FIELD_TYPE_VECTOR4D = 23,
	SCHEMA_FIELD_TYPE_QANGLE = 24,
	SCHEMA_FIELD_TYPE_QUATERNION = 25,
	SCHEMA_FIELD_TYPE_VMATRIX = 26,
	SCHEMA_FIELD_TYPE_FLTX4 = 27,
	SCHEMA_FIELD_TYPE_COLOR = 28,
	SCHEMA_FIELD_TYPE_UNIQUEID = 29,
	SCHEMA_FIELD_TYPE_BOOL = 30,
	SCHEMA_FIELD_TYPE_RESOURCE_STRING = 31,
	SCHEMA_FIELD_TYPE_VOID = 32,
	SCHEMA_FIELD_TYPE_MATRIX3X4 = 33,
	SCHEMA_FIELD_TYPE_UTLSYMBOL = 34,
	SCHEMA_FIELD_TYPE_UTLSTRING = 35,
	SCHEMA_FIELD_TYPE_MATRIX3X4A = 36,
	SCHEMA_FIELD_TYPE_UTLBINARYBLOCK = 37,
	SCHEMA_FIELD_TYPE_UUID = 38,
	SCHEMA_FIELD_TYPE_OPAQUE_TYPE = 39,
	SCHEMA_FIELD_TYPE_TRANSFORM = 40,
	SCHEMA_FIELD_TYPE_DEF_REFERENCE = 41,
	SCHEMA_FIELD_TYPE_RADIANEULER = 42,
	SCHEMA_FIELD_TYPE_DEGREEEULER = 43,
	SCHEMA_FIELD_TYPE_FOURVECTORS = 44,
	SCHEMA_FIELD_TYPE_COUNT = 45,
};