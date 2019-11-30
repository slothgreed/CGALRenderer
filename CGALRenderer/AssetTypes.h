#ifndef ASSET_TYPES_H
#define ASSET_TYPES_H

namespace KI
{

enum VERTEX_ATTRIB
{
	VERTEX_ATTRIB_POSITION = 0,
	VERTEX_ATTRIB_NORMAL	= 1,
	VERTEX_ATTRIB_COLOR		= 2,
	VERTEX_ATTRIB_TEXCOORD	= 3,
	VERTEX_ATTRIB_NUM		= 4
};

// Point Normal Color Texcoord 以外は別クラスで実装
enum VERTEX_LAYOUT
{
	VERTEX_LAYOUT_P,	// Point
	VERTEX_LAYOUT_PN,	// Point Normal
	VERTEX_LAYOUT_PC,	// Point Color
	VERTEX_LAYOUT_PT,	// Point Texcoord
	VERTEX_LAYOUT_PNC,	// Point Normal Color
	VERTEX_LAYOUT_PNCT,	// Point Normal Color Texcoord
	VERTEX_LAYOUT_NUM,
};

}
#endif ASSET_TYPES_H
