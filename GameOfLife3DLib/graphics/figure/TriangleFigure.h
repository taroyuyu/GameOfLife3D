#ifndef GRAPHICS_TRIANGLEFIGURE_H_
#define GRAPHICS_TRIANGLEFIGURE_H_

#include "graphics/GraphicsCommon.h"
#include "graphics/color/IColor.h"
#include "graphics/color/ColorUtil.h"
#include "graphics/color/ColorValue.h"
#include "graphics/color/ColorPatternUtil.h"
#include "graphics/figure/IFigure.h"
#include "graphics/decorator/IDecorator.h"
#include "graphics/filter/IGeometryFilter.h"
#include "graphics/figure/GeometryFilterWorkSet.h"

namespace graphics
{
namespace figure
{
// �O�p�`
class TriangleFigure :
    public graphics::figure::IFigure,
    public std::enable_shared_from_this<graphics::figure::TriangleFigure>
{
public:
    enum TRIANGLE_DIRECTION {
        TRIANGLE_DIRECTION_LEFT,
        TRIANGLE_DIRECTION_TOP,
        TRIANGLE_DIRECTION_RIGHT,
        TRIANGLE_DIRECTION_BOTTOM,
    };

private:
    // �v���p�e�B���ύX���ꂽ�ꍇtrue
    bool m_propertyChanged;
    // �O�p�`�̌����i�㉺���E�j
    TRIANGLE_DIRECTION m_direction;
    // x���W
    FLOAT m_x;
    // y���W
    FLOAT m_y;
    // ��
    FLOAT m_width;
    // ����
    FLOAT m_height;
    // �}�`�̐F
    graphics::color::ColorValue m_color;
    // �}�`�̌`��i��{�ƂȂ�`��j
    CComPtr<ID2D1PathGeometry> m_pGeometry;
    // �e���ʂ�����ꍇtrue
    bool m_shadow;
    // �J���[�p�^�[�����������邽�߂ɗp����}�`�̌`��
    std::vector<CComPtr<ID2D1PathGeometry>> m_frames;
    // �J���[�p�^�[�����������邽�߂ɗp���镡���̃u���V
    //std::vector<std::shared_ptr<graphics::brush::LinearGradientBrush>> m_brushes;
    std::unique_ptr<graphics::brush::BrushSet> m_brushes;
    // �e���ʂ̐F
    std::shared_ptr<graphics::color::IColor> m_shadowColor;
    // �f�R���[�^
    std::vector<std::shared_ptr<graphics::decorator::IDecorator>> m_decorators;
    // �W�I���g���t�B���^
    std::vector<graphics::figure::GeometryFilterWorkSet> m_geometryFilter;

protected:
    // �O�p�`�̌`��̐���
    HRESULT _CreateTriangleGeometry(
        IN ID2D1Factory *factory,
        IN D2D1_RECT_F rect,
        IN TRIANGLE_DIRECTION triangleDirection,
        OUT ID2D1PathGeometry **geometry);

public:
    // �R���X�g���N�^
    TriangleFigure(void);
    // �f�X�g���N�^
    virtual ~TriangleFigure(void);

    // �C���^�[�t�F�C�X graphics::figure::IFigure (�J�n)
    virtual void SetX(FLOAT x) {
        m_x = x;
        m_propertyChanged = true;
    }
    virtual FLOAT GetX() const {
        return m_x;
    }
    virtual void SetY(FLOAT y) {
        m_y = y;
        m_propertyChanged = true;
    }
    virtual FLOAT GetY() const {
        return m_y;
    }
    virtual void SetWidth(FLOAT width) {
        m_width = width;
        m_propertyChanged = true;
    }
    virtual FLOAT GetWidth() const {
        return m_width;
    }
    virtual void SetHeight(FLOAT height) {
        m_height = height;
        m_propertyChanged = true;
    }
    virtual FLOAT GetHeight() const {
        return m_height;
    }
    virtual void SetColor(
        const graphics::color::ColorValue &colorValue,
        graphics::color::COLOR_PATTERN colorPattern = graphics::color::COLOR_PATTERN_FLAT);
    virtual HRESULT Initialize(
        graphics::D3DInteropHelper *pD3DInteropHelper);
    virtual HRESULT CreateDeviceDependentResources(
        graphics::D3DInteropHelper *pD3DInteropHelper,
        ID2D1RenderTarget *pRenderTarget);
    virtual HRESULT Render(
        graphics::D3DInteropHelper *pD3DInteropHelper,
        ID2D1RenderTarget *pRenderTarget,
        FLOAT opacity);
    virtual void DiscardDeviceDependentResources();
    virtual bool HitTest(FLOAT x, FLOAT y) {
        return (m_x <= x && x <= (m_x + m_width)) &&
               (m_y <= y && y <= (m_y + m_height));
    }
    virtual void AddDecorator(std::shared_ptr<graphics::decorator::IDecorator> decorator) {
        m_decorators.push_back(decorator);
    }
    virtual void ClearDecorators() {
        m_decorators.clear();
    }
    // �W�I���g���[�t�B���^�[�̒ǉ�
    virtual void AddGeometryFilter(
        const std::wstring &workSetName,
        const std::wstring &filterName,
        FILTER_DISPLAY_ORDER filterDispayOrder,
        std::shared_ptr<graphics::color::IColor> color) {
        m_geometryFilter.push_back(
            graphics::figure::GeometryFilterWorkSet(workSetName, filterName, filterDispayOrder, color));
    }
    // �t�B���^�[�����݂��邩�ǂ����̃e�X�g
    virtual bool HasGeometryFilter(const std::wstring &workSetName) {
        return std::find_if(m_geometryFilter.begin(), m_geometryFilter.end(), [&](graphics::figure::GeometryFilterWorkSet & e) {
            return e.GetWorkSetName() == workSetName;
        }) != m_geometryFilter.end();
    }
    // �W�I���g���[�t�B���^�[�̍폜
    virtual void ClearGeometryFilters() {
        m_geometryFilter.clear();
    }
    // �C���^�[�t�F�C�Xgraphics::figure::IFigure (�I��)

    void SetDirection(graphics::figure::TriangleFigure::TRIANGLE_DIRECTION direction) {
        m_direction = direction;
        m_propertyChanged = true;
    }
    graphics::figure::TriangleFigure::TRIANGLE_DIRECTION GetDirection() const {
        return m_direction;
    }
    void SetShadow(bool shadow) {
        m_shadow = shadow;
        m_propertyChanged = true;
    }
    bool HasShadow() const {
        return m_shadow;
    }
    // �e���ʂ̐F�̐ݒ�
    void SetShadowColor(std::shared_ptr<graphics::color::IColor> shadowColor) {
        m_shadowColor = shadowColor;
        m_propertyChanged = true;
    }
    // �e���ʂ̐F�̎擾
    std::shared_ptr<graphics::color::IColor> GetShadowColor() const {
        return m_shadowColor;
    }
};
}
}

#endif // GRAPHICS_TRIANGLEFIGURE_H_