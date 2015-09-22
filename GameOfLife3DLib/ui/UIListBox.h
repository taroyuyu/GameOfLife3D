#ifndef UI_UILISTBOX_H_
#define UI_UILISTBOX_H_

#include "graphics/GraphicsCommon.h"
#include "ui/UICommon.h"
#include "ui/UIBase.h"
#include "ui/UIContainer.h"
#include "ui/UIScrollBar.h"

namespace ui {

  class UIListBox : public UIContainer, public std::enable_shared_from_this<UIListBox> {
  public:
    // �X�N���[������
    enum SCROLL_DIRECTION { SCROLL_DIRECTION_HORIZONTAL, SCROLL_DIRECTION_VERTICAL };

  private:
    // �X�N���[������
    SCROLL_DIRECTION m_scrollDirection;
    // ��]����r�b�g�}�b�v�T�C�Y �i�f�t�H���g��64x64�j
    UISize m_preferredBitmapSize;
    // ��]����e�L�X�g�� (�}�C�i�X�̏ꍇ�A�r�b�g�}�b�v�T�C�Y��莩���v�Z�j
    UISize m_preferredTextAreaSize;
    // �r�b�g�}�b�v�ƃe�L�X�g�̊Ԃ̃}�[�W��
    FLOAT m_marginBetweenBitmapAndText;
    // �A�C�e���Ԃ̊Ԋu �i�f�t�H���g��4�j
    FLOAT m_marginBetweenItems;
    // �A�C�e���̕�
    FLOAT m_itemWidth;
    // �A�C�e���̍���
    FLOAT m_itemHeight;
    // �X�N���[���o�[�̃T�C�h����̊Ԋu�@�i�f�t�H���g��8�j
    FLOAT m_scrollBarMarginFromSide;
    // �X�N���[���o�[�̑����i�f�t�H���g��12�j
    FLOAT m_scrollBarThick;
    // ���X�g�{�b�N�X��`�悷�邽�߂̃t�B�M���A
    std::unique_ptr<graphics::figure::RectangleFigure> m_rectFigure;
    // ���X�g�{�b�N�X��`�悷�邽�߂̃J���[�Z�b�g
    std::shared_ptr<graphics::color::ColorSet> m_colorSet;
    // �X�N���[���o�[
    std::shared_ptr<ui::UIScrollBar> m_scrollBar;
    // �X�N���[���o�[�̈ʒu����v�Z�����\���ʒu�I�t�Z�b�g
    FLOAT m_displayPositionOffset;

  public:
    // �R���X�g���N�^
    UIListBox(SCROLL_DIRECTION scrollDirection = SCROLL_DIRECTION_VERTICAL,
              UISize preferredBitmapSize = UISize(64, 64));
    // �f�X�g���N�^
    virtual ~UIListBox(void);
    // �R���|�[�l���g�̏�����
    virtual HRESULT Initialize(graphics::D3DInteropHelper *pD3DInteropHelper);
    // �R���|�[�l���g�̃��C�A�E�g
    virtual HRESULT LayoutComponents();
    // �f�o�C�X�ˑ����\�[�X�̐���
    virtual HRESULT CreateDeviceDependentResources(graphics::D3DInteropHelper *pD3DInteropHelper,
                                                   ID2D1RenderTarget *pRenderTarget);
    // �`��
    virtual HRESULT Render(graphics::D3DInteropHelper *pD3DInteropHelper, ID2D1RenderTarget *pRenderTarget);
    // �f�o�C�X�ˑ����\�[�X�̔j��
    virtual void DiscardDeviceDependentResources();

    // ��]����r�b�g�}�b�v�T�C�Y�̐ݒ�
    void SetPreferredBitmapSize(UISize preferredBitmapSize) {
      m_preferredBitmapSize = preferredBitmapSize;
    }
    // ��]����e�L�X�g�̈�T�C�Y�̐ݒ�
    void SetPreferredTextAreaSize(UISize preferredTextAreaSize) {
      m_preferredTextAreaSize = preferredTextAreaSize;
    }
    // �A�C�e���Ԃ̃}�[�W���̐ݒ�
    void SetMarginBetweenItems(FLOAT marginBetweenItems) {
      m_marginBetweenItems = marginBetweenItems;
    }
    // �X�N���[�������̐ݒ�
    void SetScrollDirection(SCROLL_DIRECTION scrollDirection) {
      m_scrollDirection = scrollDirection;
    }
    // �t�H�[�J�X�擾�̒ʒm
    virtual void NotifyFocusObtained(const std::shared_ptr<UIBase> &uiBase);

    // scroll position changed
    void NotifyScrollPositionChanged(FLOAT position);

    // events
    virtual void OnLeftMouseDown(HWND hWnd, WPARAM wParam, LPARAM lParam, UIPoint clientPoint,
                                 ULONGLONG timestampInMilliSeconds, OUT bool *eaten);
    virtual void OnDraggingStart(HWND hWnd, WPARAM wParam, LPARAM lParam, UI2Points clientDragRect, UIDelta delta,
                                 ULONGLONG timestampInMilliSeconds, OUT bool *eaten);
    virtual void OnDragging(HWND hWnd, WPARAM wParam, LPARAM lParam, UI2Points clientDragRect, UIDelta delta,
                            ULONGLONG timestampInMilliSeconds, OUT bool *eaten);
    virtual void OnDraggingEnd(HWND hWnd, WPARAM wParam, LPARAM lParam, UI2Points clientDragRect, UIDelta delta,
                               ULONGLONG timestampInMilliSeconds, OUT bool *eaten);
    virtual void OnMouseOver(HWND hWnd, WPARAM wParam, LPARAM lParam, UIPoint clientPoint, UIDelta delta,
                             ULONGLONG timestampInMilliSeconds, OUT bool *eaten);
    virtual void OnMouseOut(HWND hWnd, WPARAM wParam, LPARAM lParam, UIPoint clientPoint, UIDelta delta,
                            ULONGLONG timestampInMilliSeconds, OUT bool *eaten);
    virtual void OnRightSingleClick(HWND hWnd, WPARAM wParam, LPARAM lParam, UIPoint clientPoint,
                                    ULONGLONG timestampInMilliSeconds, OUT bool *eaten);
    virtual void OnGestureBegin(HWND hWnd, WPARAM wParam, LPARAM lParam, UIPoint clientPoint, PGESTUREINFO pGestureInfo,
                                ULONGLONG timestampInMilliSeconds, OUT bool *eaten);
    virtual void OnGestureEnd(HWND hWnd, WPARAM wParam, LPARAM lParam, UIPoint clientPoint, PGESTUREINFO pGestureInfo,
                              ULONGLONG timestampInMilliSeconds, OUT bool *eaten);
    virtual void OnPan(HWND hWnd, WPARAM wParam, LPARAM lParam, UIPoint clientPoint, PGESTUREINFO pGestureInfo,
                       UIDelta delta, ULONGLONG timestampInMilliSeconds, OUT bool *eaten);
    virtual void OnPressAndTap(HWND hWnd, WPARAM wParam, LPARAM lParam, UIPoint clientPoint, PGESTUREINFO pGestureInfo,
                               ULONGLONG timestampInMilliSeconds, OUT bool *eaten);
  };
}

#endif // UI_UILISTBOX_H_
