#ifndef ShapeTypeSequenceDataReader_h__
#define ShapeTypeSequenceDataReader_h__
/*************************************************************/
/*           ���ļ��ɱ��������ɣ����������޸�                */
/*************************************************************/

#include "ShapeTypeSequence.h"
#include "ZRDDSDataReader.h"

typedef struct ShapeTypeSequenceSeq ShapeTypeSequenceSeq;

typedef DDS::ZRDDSDataReader<ShapeTypeSequence, ShapeTypeSequenceSeq> ShapeTypeSequenceDataReader;

#endif

