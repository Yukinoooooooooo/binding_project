#ifndef ShapeTypeDataReader_h__
#define ShapeTypeDataReader_h__


#include "ShapeType.h"
#include "ZRDDSDataReader.h"

typedef struct ShapeTypeSeq ShapeTypeSeq;

typedef DDS::ZRDDSDataReader<ShapeType, ShapeTypeSeq> ShapeTypeDataReader;

#endif

