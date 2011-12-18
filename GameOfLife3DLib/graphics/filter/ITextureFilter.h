#ifndef GRAPHICS_ITEXTUREFILTER_H_
#define GRAPHICS_ITEXTUREFILTER_H_

#include "graphics/GraphicsCommon.h"

namespace graphics
{
namespace filter
{
class ITextureFilter
{
public:
    virtual HRESULT Initialize() = 0;
    // �e�N�X�`���t�B���^�[�̓K�p
    // �o�͐�̃e�N�X�`���́ACalculateMargins����v�Z���ꂽ�}�[�W�������e�N�X�`���T�C�Y
    // �̂��̂��쐬���Ă����Ȃ���΂Ȃ�Ȃ��B
    virtual HRESULT ApplyFilter(
        IN graphics::D3DInteropHelper *pD3DInteropHelper,
        IN ID3D10Texture2D *pSourceTexture,
        OUT ID3D10Texture2D **ppOutputTexture
    ) = 0;
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

#endif // GRAPHICS_ITEXTUREFILTER_H_