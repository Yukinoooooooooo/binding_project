/*************************************************************/
/*           ���ļ��ɱ��������ɣ����������޸�                */
/*************************************************************/
#include <stdlib.h>
#include "ZRDDSTypePlugin.h"
#include "ShapeType.h"
#include "ShapeTypeTypeSupport.h"
#include "ShapeTypeDataReader.h"
#include "ShapeTypeDataWriter.h"
#include "ZRDDSTypeSupport.cpp"


const DDS_Char* ShapeType_TYPENAME = "ShapeType";
DDSTypeSupportImpl(ShapeTypeTypeSupport, ShapeType, ShapeType_TYPENAME);

