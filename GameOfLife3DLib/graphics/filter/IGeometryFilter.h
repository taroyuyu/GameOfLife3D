#ifndef GRAPHICS_IGEOMETRYFILTER_H_
#define GRAPHICS_IGEOMETRYFILTER_H_

#include "graphics/GraphicsCommon.h"

namespace graphics
{
namespace filter
{
class IGeometryFilter
{
public:
    virtual HRESULT Initialize() = 0;
    // �W�I���g���t�B���^�[�̓K�p
    // width��height�ɂ́A�ʏ��ID2D1Geometry��GetBounds���瓾����l��^����΂悢�B
    // �����A�t�B���^�[�ɂ���Ă̓W�I���g���Ƃ͊֌W�Ȃ������ɂ��G�t�F�N�g��K�p����ꍇ��
    // ����B���̏ꍇ�́A�K�p���Ă��炢�����̈�S�̂𕢂�width��height���w�肷��B
    virtual HRESULT ApplyFilter(
        IN graphics::D3DInteropHelper *pD3DInteropHelper,
        IN ID2D1RenderTarget *pRenderTarget,
        IN ID2D1Geometry *pGeometry,
        IN FLOAT width,
        IN FLOAT height,
        IN ID2D1Brush *pBrush,
        OUT ID2D1Bitmap **ppBitmap,
        OUT D2D1_RECT_F *pBitmapRect
    ) = 0;
    // �^����ꂽwidth��height����A�㉺���E�̃}�[�W���i�ǉ������̈�j���v�Z����B
    // ����́A�K�E�X�t�B���^�̂悤�ɐ}�`�̎���Ɍ��ʂ��쐬����t�B���^�[�̏ꍇ��
    // width��height���傫���Ȃ邽�߂ɕK�v�ƂȂ�B
    virtual void CalculateMargins(
        IN FLOAT width, IN FLOAT height,
        OUT FLOAT &leftMargin,
        OUT FLOAT &topMargin,
        OUT FLOAT &rightMargin,
        OUT FLOAT &bottomMargin
    ) = 0;
};
}
}

#endif // GRAPHICS_IGEOMETRYFILTER_H_