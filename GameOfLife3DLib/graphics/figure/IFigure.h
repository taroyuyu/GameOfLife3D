#ifndef GRAPHICS_FIGURE_IFIGURE_H_
#define GRAPHICS_FIGURE_IFIGURE_H_

#include "graphics/GraphicsCommon.h"
#include "graphics/decorator/IDecorator.h"

namespace graphics
{
namespace figure
{
enum FILTER_DISPLAY_ORDER {
    FILTER_DISPLAY_ORDER_BEFORE_FIGURE,
    FILTER_DISPLAY_ORDER_AFTER_FIGURE,
};

// �}�`
class IFigure
{
public:
    // X���W�̐ݒ�
    virtual void SetX(FLOAT x) = 0;
    // X���W�̎擾
    virtual FLOAT GetX() const = 0;
    // Y���W�̐ݒ�
    virtual void SetY(FLOAT y) = 0;
    // Y���W�̎擾
    virtual FLOAT GetY() const = 0;
    // ���̐ݒ�
    virtual void SetWidth(FLOAT width) = 0;
    // ���̎擾
    virtual FLOAT GetWidth() const = 0;
    // �����̐ݒ�
    virtual void SetHeight(FLOAT height) = 0;
    // �����̎擾
    virtual FLOAT GetHeight() const = 0;
    // �}�`�̐F�̐ݒ�
    //   �J���[�p�^�[����ݒ肵���ꍇ�A���̃J���[�p�^�[���ɏ]���ĕ\�������B��̓I�ɂǂ̂悤�ɕ\������邩��
    //   �X�̐}�`�̎����ɂ��B
    //   �J���[�p�^�[�����w�肵�Ȃ������ꍇ�A�w�肵���P�F�œh��Ԃ����B
    virtual void SetColor(
        const graphics::color::ColorValue &colorValue,
        graphics::color::COLOR_PATTERN colorPattern = graphics::color::COLOR_PATTERN_FLAT) = 0;
    // ������
    virtual HRESULT Initialize(
        graphics::D3DInteropHelper *pD3DInteropHelper) = 0;
    // �f�o�C�X�ˑ����\�[�X�̐���
    virtual HRESULT CreateDeviceDependentResources(
        graphics::D3DInteropHelper *pD3DInteropHelper,
        ID2D1RenderTarget *pRenderTarget) = 0;
    // �`��
    virtual HRESULT Render(
        graphics::D3DInteropHelper *pD3DInteropHelper,
        ID2D1RenderTarget *pRenderTarget,
        FLOAT opacity) = 0;
    // �f�o�C�X�ˑ����\�[�X�̔j��
    virtual void DiscardDeviceDependentResources() = 0;
    // �q�b�g�e�X�g
    virtual bool HitTest(FLOAT x, FLOAT y) = 0;
    // �f�R���[�^�̒ǉ�
    virtual void AddDecorator(const std::shared_ptr<graphics::decorator::IDecorator> &decorator) = 0;
    // �f�R���[�^�̃N���A
    virtual void ClearDecorators() = 0;
    // �t�B���^�[�̒ǉ�
    virtual void AddGeometryFilter(
        const std::wstring &workSetName,
        const std::wstring &filterName,
        FILTER_DISPLAY_ORDER filterDispayOrder,
        std::shared_ptr<graphics::color::IColor> color) = 0;
    // �t�B���^�[�����݂��邩�ǂ����̃e�X�g
    virtual bool HasGeometryFilter(const std::wstring &workSetName) = 0;
    // �t�B���^�[�̍폜
    virtual void ClearGeometryFilters() = 0;
};
}
}

#endif // GRAPHICS_FIGURE_IFIGURE_H_
