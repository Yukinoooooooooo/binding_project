/*************************************************************/
/*           ���ļ��ɱ��������ɣ����������޸�                */
/*************************************************************/
#include <stdlib.h>
#include "ZRDDSTypePlugin.h"
#include "ShapeTypeSequence.h"
#include "ShapeTypeSequenceTypeSupport.h"
#include "ShapeTypeSequenceDataReader.h"
#include "ShapeTypeSequenceDataWriter.h"
#include "ZRDDSTypeSupport.cpp"


const DDS_Char* ShapeTypeSequence_TYPENAME = "ShapeTypeSequence";
DDSTypeSupportImpl(ShapeTypeSequenceTypeSupport, ShapeTypeSequence, ShapeTypeSequence_TYPENAME);

