#include "Stdafx.h"
#include "graphics/color/ColorSet.h"
#include "graphics/color/IColor.h"
#include "graphics/color/SolidColor.h"
#include "graphics/color/LinearGradientColor.h"
#include "graphics/color/RadialGradientColor.h"
#include "graphics/color/colorsetdef/ColorSetDef.h"
#include "util/StringUtil.h"

using namespace graphics::color;
using namespace graphics::color::colorsetdef;

ColorValue ConvertColorValue(const ColorValueDO &src)
{
    ColorValue::COLOR_TYPE colorType =
        src.colorValueType == COLORVALUE_TYPE_RGBA ?
        ColorValue::COLOR_TYPE_RGBA : ColorValue::COLOR_TYPE_HSBA;
    return ColorValue(colorType, src.value1, src.value2, src.value3, src.value4);
}

std::shared_ptr<SolidColor> ConvertSolidColor(std::shared_ptr<SolidColorDO> src)
{
    std::shared_ptr<SolidColor> dest = std::make_shared<SolidColor>();
    dest->SetColor(ConvertColorValue(src->colorValue));
    return dest;
}

std::shared_ptr<LinearGradientColor> ConvertLinearGradientColor(std::shared_ptr<LinearColorDO> src)
{
    std::shared_ptr<LinearGradientColor> dest = std::make_shared<LinearGradientColor>();
    dest->SetGradientDirection(
        src->direction == LinearColorDO::DIRECTION_TOP_BOTTOM ?
        graphics::GRADIENT_DIRECTION_TOP_BOTTOM :
        graphics::GRADIENT_DIRECTION_TOPLEFT_TO_BOTTOMRIGHT
    );
    GradientStopCollection gradientStopCollection;
    for (auto it = src->colorValues.begin(); it != src->colorValues.end(); ++it) {
        ColorValueDO &colorValue = *it;
        gradientStopCollection.AddGradientStop(GradientStop(colorValue.position, ConvertColorValue(colorValue)));
    }
    dest->SetColor(gradientStopCollection);
    return dest;
}

std::shared_ptr<RadialGradientColor> ConvertRadialGradientColor(std::shared_ptr<RadialColorDO> src)
{
    std::shared_ptr<RadialGradientColor> dest = std::make_shared<RadialGradientColor>();
    dest->SetGradientOffset(src->offsetX, src->offsetY);
    GradientStopCollection gradientStopCollection;
    for (auto it = src->colorValues.begin(); it != src->colorValues.end(); ++it) {
        ColorValueDO &colorValue = *it;
        gradientStopCollection.AddGradientStop(GradientStop(colorValue.position, ConvertColorValue(colorValue)));
    }
    dest->SetColor(gradientStopCollection);
    return dest;
}

void graphics::color::ColorSet::AddColors(const wchar_t *colorDesc)
{
    std::shared_ptr<ColorSetDO> colorSet =
        graphics::color::colorsetdef::Decode(colorDesc);

    for (auto it = colorSet->colors.begin(); it != colorSet->colors.end(); ++it) {
        std::shared_ptr<IColorDO> color = *it;
        switch (color->GetColorType()) {
        case graphics::color::colorsetdef::COLOR_TYPE_SOLID: {
            std::shared_ptr<SolidColorDO> solidColorDO =
                std::dynamic_pointer_cast<SolidColorDO>(color);
            std::shared_ptr<SolidColor> solidColor = ConvertSolidColor(solidColorDO);
            m_colors.push_back(solidColor);
            if (solidColorDO->label.length() > 0) {
                solidColor->SetLabel(solidColorDO->label);
                m_labelToColorMap.insert(
                    std::make_pair<std::wstring, std::shared_ptr<IColor>>(solidColorDO->label, solidColor));
            }
        }
        break;
        case graphics::color::colorsetdef::COLOR_TYPE_LINEAR: {
            std::shared_ptr<LinearColorDO> linearColorDO =
                std::dynamic_pointer_cast<LinearColorDO>(color);
            std::shared_ptr<LinearGradientColor> linearColor = ConvertLinearGradientColor(linearColorDO);
            m_colors.push_back(linearColor);
            if (linearColorDO->label.length() > 0) {
                linearColor->SetLabel(linearColorDO->label);
                m_labelToColorMap.insert(
                    std::make_pair<std::wstring, std::shared_ptr<IColor>>(linearColorDO->label, linearColor));
            }
        }
        break;
        case graphics::color::colorsetdef::COLOR_TYPE_RADIAL: {
            std::shared_ptr<RadialColorDO> radialColorDO =
                std::dynamic_pointer_cast<RadialColorDO>(color);
            std::shared_ptr<RadialGradientColor> radialColor = ConvertRadialGradientColor(radialColorDO);
            m_colors.push_back(radialColor);
            if (radialColorDO->label.length() > 0) {
                radialColor->SetLabel(radialColorDO->label);
                m_labelToColorMap.insert(
                    std::make_pair<std::wstring, std::shared_ptr<IColor>>(radialColorDO->label, radialColor));
            }
        }
        break;
        }
    }
}


void graphics::color::ColorSet::AddColor( std::shared_ptr<graphics::color::IColor> color )
{
    m_colors.push_back(color);
    if (color->GetLabel().length() > 0) {
        m_labelToColorMap.insert(
            std::make_pair<std::wstring, std::shared_ptr<graphics::color::IColor>>(color->GetLabel(), color));
    }
}


void graphics::color::ColorSet::Clear()
{
    m_colors.clear();
    m_labelToColorMap.clear();
}