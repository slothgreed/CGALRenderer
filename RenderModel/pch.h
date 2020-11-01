﻿// pch.h: プリコンパイル済みヘッダー ファイルです。
// 次のファイルは、その後のビルドのビルド パフォーマンスを向上させるため 1 回だけコンパイルされます。
// コード補完や多くのコード参照機能などの IntelliSense パフォーマンスにも影響します。
// ただし、ここに一覧表示されているファイルは、ビルド間でいずれかが更新されると、すべてが再コンパイルされます。
// 頻繁に更新するファイルをここに追加しないでください。追加すると、パフォーマンス上の利点がなくなります。

#ifndef RENDER_MODEL_PCH_H
#define RENDER_MODEL_PCH_H

#ifndef DLL_EXPORT
#define DLL_EXPORT  __declspec(dllexport)
#endif

using namespace std;

// Foundation
#include "../KIFoundation/pch.h"
using namespace KI::Foundation;

#include "../KIGfx/pch.h"
using namespace KI::Gfx;

#include "../KIShaderLib/pch.h"
using namespace KI::ShaderLib;

#include "../KIRenderer/pch.h"
using namespace KI::Renderer;

#include "../KITopology/pch.h"
using namespace KI::Topology;

#include "../KIAlgorithm/pch.h"
using namespace KI::Algorithm;

#include "../KIAsset/pch.h"
using namespace KI::Asset;

#include "BDBProperty.h"
#include "NormalProperty.h"
#include "HalfEdgeProperty.h"
#include "PrimitiveNode.h"
#include "PolygonModelNode.h"
#include "HalfEdgeDSNode.h"
#include "ManipulatorNode.h"
#include "BezierLineNode.h"
#include "CameraNode.h"

#endif //RENDER_MODEL_PCH_H
