#ifndef GRAPHICS_BRUSH_BRUSHSET_H_
#define GRAPHICS_BRUSH_BRUSHSET_H_

#include "graphics/brush/IBrush.h"
#include "graphics/color/IColor.h"
#include "graphics/color/ColorSet.h"

namespace graphics
{
namespace brush
{
// �u���V�Z�b�g - �����̃u���V����ɂ܂Ƃ߂��N���X
class BrushSet
{
private:
    // �u���V���i�[�����x�N�^
    std::vector<std::shared_ptr<graphics::brush::IBrush>> m_brushes;
    // ���x���ƃu���V�̃}�b�v
    std::unordered_map<std::wstring, std::shared_ptr<graphics::brush::IBrush>> m_labelToBrashMap;
    // �f�o�C�X�ˑ����\�[�X���������ꂽ���ǂ���
    bool m_deviceDependentResourceCreated;

public:
    // �R���X�g���N�^
    BrushSet() :
        m_brushes(),
        m_labelToBrashMap(),
        m_deviceDependentResourceCreated(false)
    {}
    // �R���X�g���N�^�i�w�肳�ꂽ�J���[�Z�b�g����u���V���쐬�j
    BrushSet(const graphics::color::ColorSet &colorSet) :
        m_brushes(colorSet.GetNumberOfColors()),
        m_labelToBrashMap(),
        m_deviceDependentResourceCreated(false) {
        SetColorSet(colorSet);
    }
    // �R���X�g���N�^�i�w�肳�ꂽ�J���[�Z�b�g����u���V���쐬�j
    BrushSet(const std::shared_ptr<graphics::color::ColorSet> &colorSet) :
        m_brushes(colorSet->GetNumberOfColors()),
        m_labelToBrashMap(),
        m_deviceDependentResourceCreated(false) {
        SetColorSet(colorSet);
    }
    // �f�X�g���N�^
    ~BrushSet() {}
    // �u���V�̃f�o�C�X�ˑ����\�[�X�̐���
    // �w�肳�ꂽ�̈�ɍ����悤�Ƀu���V�����������B�����̈��ύX�������ꍇ��
    // GetBrush�̈����Ɏw�肷��B
    // opacity�̓u���V�̕s�����x���w�肷��B�����s�����x��ύX�������ꍇ��
    // GetBrush�̈����Ɏw�肷��B
    HRESULT CreateDeviceDependentResource(
        ID2D1RenderTarget *pRenderTarget,
        const D2D1_RECT_F &rect,
        FLOAT opacity);
    // �u���V�̒ǉ�
    void AddBrush(const std::shared_ptr<graphics::brush::IBrush> &brush) {
        m_brushes.push_back(brush);
    }
    // �u���V�̒ǉ�
    void AddBrush(const std::shared_ptr<graphics::brush::IBrush> &brush, const std::wstring &label) {
        m_brushes.push_back(brush);
        m_labelToBrashMap.insert({ label, brush });
    }
    // �u���V�̃N���A�i���ׂẴu���V���j�������j
    void Clear() {
        m_brushes.clear();
        m_labelToBrashMap.clear();
    }
    // �u���V����Ԃ�
    size_t GetNumberOfBrushes() const {
        return m_brushes.size();
    }
    // �w�肳�ꂽ�C���f�b�N�X�̃u���V��Ԃ�
    std::shared_ptr<IBrush> Get(size_t index) const {
        return m_brushes[index];
    }
    // ���x������u���V��Ԃ�
    std::shared_ptr<IBrush> Get(const std::wstring &label) const {
        if (m_labelToBrashMap.count(label) > 0) {
            return m_labelToBrashMap.at(label);
        } else {
            throw std::runtime_error("a brush which has the specified label is not found");
        }
    }
    // ���ݕێ����Ă��邷�ׂẴu���V���j������A�J���[�Z�b�g�̓��e�ɍ��킹�ău���V�����������
    void SetColorSet(const graphics::color::ColorSet &colorSet);
    // ���ݕێ����Ă��邷�ׂẴu���V���j������A�J���[�Z�b�g�̓��e�ɍ��킹�ău���V�����������
    void SetColorSet(const std::shared_ptr<graphics::color::ColorSet> &colorSet) {
        SetColorSet(*colorSet);
    }
    // ���ׂẴf�o�C�X�ˑ����\�[�X��j������
    void DiscardDeviceDependentResource();
    // �f�o�C�X�ˑ����\�[�X����������Ă��邩�ǂ���
    bool IsDeviceDependentResourceCreated() {
        return m_deviceDependentResourceCreated;
    }
};
}
}

#endif // GRAPHICS_BRUSH_BRUSHSET_H_
