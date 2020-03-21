#ifndef RENDER_TYPE_H
#define RENDER_TYPE_H
namespace KI
{
namespace Renderer
{

enum VERTEX_ATTRIB
{
	VERTEX_ATTRIB_POSITION			= 0x00,
	VERTEX_ATTRIB_NORMAL			= 0x01,
	VERTEX_ATTRIB_COLOR				= 0x02,
	VERTEX_ATTRIB_TEXCOORD			= 0x03,
	VERTEX_ATTRIB_INSTANCE_MATRIX0	= 0x04,	// row0
	VERTEX_ATTRIB_INSTANCE_MATRIX1	= 0x05,	// row1
	VERTEX_ATTRIB_INSTANCE_MATRIX2	= 0x06,	// row2
	VERTEX_ATTRIB_INSTANCE_MATRIX3	= 0x07,	// row3
	VERTEX_ATTRIB_NUM				= 0xFF
};

enum VERTEX_LAYOUT
{
	VERTEX_LAYOUT_NONE				= 0x00,
	VERTEX_LAYOUT_POSITION			= 0x01,
	VERTEX_LAYOUT_NORMAL			= 0x02,
	VERTEX_LAYOUT_COLOR				= 0x04,
	VERTEX_LAYOUT_TEXCOORD			= 0x08,
	VERTEX_LAYOUT_INSTANCE_MATRIX0	= 0x10,	// row0
	VERTEX_LAYOUT_INSTANCE_MATRIX1	= 0x20,	// row1
	VERTEX_LAYOUT_INSTANCE_MATRIX2	= 0x40,	// row2
	VERTEX_LAYOUT_INSTANCE_MATRIX3	= 0x80,	// row3
	VERTEX_LAYOUT_NUM				= 0xFF
};

enum MATERIAL_TYPE
{
	MATERIAL_TYPE_DEFAULT,
	MATERIAL_TYPE_POINTMATERIAL,
	MATERIAL_TYPE_LINEMATERIAL,
	MATERIAL_TYPE_OUTPUT_BUFFER
};
}
}

#endif RENDER_TYPE_H
