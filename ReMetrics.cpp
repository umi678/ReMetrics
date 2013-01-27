// noMeiryoUI.cpp : �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"

#include <windows.h>
#include <commdlg.h>
#include "ReMetrics.h"

#define MAX_LOADSTRING 100

//
// �_�C�A���O�x�[�X�A�v���P�[�V�����t���[�����[�N��
// ���[�U�[�����̃u���b�W���[�`��
//

// �A�v���P�[�V�����I�u�W�F�N�g
ReMetrics *appObj;

/**
 * �A�v���P�[�V�����I�u�W�F�N�g���쐬���܂��B
 */
DialogAppliBase *createAppli()
{
	// �����Ń��[�U�[�̃A�v���P�[�V�����I�u�W�F�N�g���쐬���܂��B
	appObj = new ReMetrics();
	return appObj;
}

/**
 * �_�C�A���O�v���[�V�W��
 *
 */
INT_PTR CALLBACK MainDialogProc(
  HWND hwndDlg,  // �_�C�A���O�{�b�N�X�̃n���h��
  UINT uMsg,     // ���b�Z�[�W
  WPARAM wParam, // �ŏ��̃��b�Z�[�W�p�����[�^
  LPARAM lParam  // 2 �Ԗڂ̃��b�Z�[�W�p�����[�^
  )
{
	// ���[�U�[�A�v���P�[�V�����̃_�C�A���O�v���[�V�W���Ɋۓ������܂��B
	return appObj->dialogProc(hwndDlg, uMsg,wParam,lParam);
}

//
// �_�C�A���O�x�[�X�A�v���P�[�V�����t���[�����[�N�̎�����
//

/**
 * �A�v���P�[�V�����E�C���h�E�N���X�̃C���X�^���X�𐶐����܂��B
 *
 * @return �A�v���P�[�V�����E�C���h�E�N���X�̃C���X�^���X
 */
BaseDialog *ReMetrics::createBaseDialog()
{
	borderWidthUpDown = NULL;
	titleWidthUpDown = NULL;
	titleHeightUpDown = NULL;
	scrollWidthUpDown = NULL;
	scrollHeightUpDown = NULL;
	paletteWidthUpDown = NULL;
	paletteHeightUpDown = NULL;
	menuWidthUpDown = NULL;
	menuHeightUpDown = NULL;
	paddingUpDown = NULL;

	return appObj;
}

/**
 * �A�v���P�[�V�����̊J�n���������s���܂��B
 *
 * @param lpCmdLine �R�}���h���C��
 * @return �\��
 */
int ReMetrics::OnAppliStart(TCHAR *lpCmdLine)
{
	// ���̊֐����I�[�o�[���C�h���ăA�v���ŗL�̏��������s���܂��B
	// �{�A�v���P�[�V�����ł͓��ɏ����Ȃ��B
	return 0;
}

/**
 * �E�C���h�E���\�����ꂽ�Ƃ��̏��������s���܂��B<br>
 * �E�C���h�E�x�[�X�A�v���ƃC���^�t�F�[�X�����킹�邽�߂ɗp�ӂ��Ă��܂��B
 *
 * @return �\��
 */
int ReMetrics::OnWindowShow()
{

	// ���̊֐����I�[�o�[���C�h���āA����̕\�����̏������s���܂��B
	// ���̃^�C�~���O�Ń_�C�A���O�����݂���̂ŁA�����ɏ��������邱�Ƃ�
	// �_�C�A���O�������ԂŋN�����̏������������s�����Ƃ��ł��܂��B
	DWORD dwver;

	dwver = GetVersion();

	FillMemory(&metrics,sizeof(NONCLIENTMETRICS),0x00);

	// �A�C�R���ȊO�̃t�H���g�����擾����B
	if (LOBYTE(dwver) > 5) {
		/* Windows Vista/7/8 */
		metrics.cbSize = sizeof(NONCLIENTMETRICS);
	} else {
		/* Windows 2000/XP */
		metrics.cbSize = sizeof(NONCLIENTMETRICS) - 4;
	}

	SystemParametersInfo(SPI_GETNONCLIENTMETRICS,
		metrics.cbSize,
		&metrics,
		0);

	TCHAR buf[32];

	_stprintf(buf,_T("%d"), metrics.iBorderWidth);
	borderWidth = buf;

	_stprintf(buf,_T("%d"), metrics.iCaptionWidth);
	titleWidth = buf;

	_stprintf(buf,_T("%d"), metrics.iCaptionHeight);
	titleHeight = buf;

	_stprintf(buf,_T("%d"), metrics.iScrollWidth);
	scrollWidth = buf;

	_stprintf(buf,_T("%d"), metrics.iScrollHeight);
	scrollHeight = buf;

	_stprintf(buf,_T("%d"), metrics.iSmCaptionWidth);
	paletteWidth = buf;

	_stprintf(buf,_T("%d"), metrics.iSmCaptionHeight);
	paletteHeight = buf;

	_stprintf(buf,_T("%d"), metrics.iMenuWidth);
	menuWidth = buf;

	_stprintf(buf,_T("%d"), metrics.iMenuHeight);
	menuHeight = buf;

	_stprintf(buf,_T("%d"), metrics.iPaddedBorderWidth);
	padding = _T("0");

	UpdateData(false);

	borderWidthUpDown = new TwrUpDown(::GetDlgItem(hWnd, IDC_SPIN_BORDER));
	borderWidthUpDown->setBuddy(::GetDlgItem(hWnd, IDC_EDIT_BORDER));
	borderWidthUpDown->setRange(0, 256);
	borderWidthUpDown->setPos(metrics.iBorderWidth);

	titleWidthUpDown = new TwrUpDown(::GetDlgItem(hWnd, IDC_SPIN_TITLE_WIDTH));
	titleWidthUpDown->setBuddy(::GetDlgItem(hWnd, IDC_EDIT_TITLE_WIDTH));
	titleWidthUpDown->setRange(0, 256);
	titleWidthUpDown->setPos(metrics.iCaptionWidth);

	titleHeightUpDown = new TwrUpDown(::GetDlgItem(hWnd, IDC_SPIN_TITLE_HEIGHT));
	titleHeightUpDown->setBuddy(::GetDlgItem(hWnd, IDC_EDIT_TITLE_HEIGHT));
	titleHeightUpDown->setRange(0, 256);
	titleHeightUpDown->setPos(metrics.iCaptionHeight);

	scrollWidthUpDown = new TwrUpDown(::GetDlgItem(hWnd, IDC_SPIN_SCROLL_WIDTH));
	scrollWidthUpDown->setBuddy(::GetDlgItem(hWnd, IDC_EDIT_SCROLL_WIDTH));
	scrollWidthUpDown->setRange(0, 256);
	scrollWidthUpDown->setPos(metrics.iScrollWidth);

	scrollHeightUpDown = new TwrUpDown(::GetDlgItem(hWnd, IDC_SPIN_SCROLL_HEIGHT));
	scrollHeightUpDown->setBuddy(::GetDlgItem(hWnd, IDC_EDIT_SCROLL_HEIGHT));
	scrollHeightUpDown->setRange(0, 256);
	scrollHeightUpDown->setPos(metrics.iScrollHeight);

	paletteWidthUpDown = new TwrUpDown(::GetDlgItem(hWnd, IDC_SPIN_PALETTE_WIDTH));
	paletteWidthUpDown->setBuddy(::GetDlgItem(hWnd, IDC_EDIT_PALETTE_WIDTH));
	paletteWidthUpDown->setRange(0, 256);
	paletteWidthUpDown->setPos(metrics.iSmCaptionWidth);

	paletteHeightUpDown = new TwrUpDown(::GetDlgItem(hWnd, IDC_SPIN_PALETTE_HEIGHT));
	paletteHeightUpDown->setBuddy(::GetDlgItem(hWnd, IDC_EDIT_PALETTE_HEIGHT));
	paletteHeightUpDown->setRange(0, 256);
	paletteHeightUpDown->setPos(metrics.iSmCaptionHeight);

	menuWidthUpDown = new TwrUpDown(::GetDlgItem(hWnd, IDC_SPIN_MENU_WIDTH));
	menuWidthUpDown->setBuddy(::GetDlgItem(hWnd, IDC_EDIT_MENU_WIDTH));
	menuWidthUpDown->setRange(0, 256);
	menuWidthUpDown->setPos(metrics.iMenuWidth);

	menuHeightUpDown = new TwrUpDown(::GetDlgItem(hWnd, IDC_SPIN_MENU_HEIGHT));
	menuHeightUpDown->setBuddy(::GetDlgItem(hWnd, IDC_EDIT_MENU_HEIGHT));
	menuHeightUpDown->setRange(0, 256);
	menuHeightUpDown->setPos(metrics.iMenuHeight);

	paddingUpDown = new TwrUpDown(::GetDlgItem(hWnd, IDC_SPIN_PADDING));
	paddingUpDown->setBuddy(::GetDlgItem(hWnd, IDC_EDIT_PADDING));
	paddingUpDown->setRange(0, 256);
	paddingUpDown->setPos(metrics.iPaddedBorderWidth);

	return 0;
}

/**
 * �A�v���P�[�V�����̏I�����������s���܂��B
 *
 * @return �\��
 */
int ReMetrics::OnAppliEnd()
{
	// ���̊֐����I�[�o�[���C�h���ăA�v���ŗL�̌㏈�����s���܂��B
	// �{�A�v���P�[�V�����ł͓��ɏ����Ȃ��B
	return 0;
}

//
// �_�C�A���O�x�[�X�A�v���P�[�V�����Ƃ��Ă�
// �A�v���P�[�V�����ŗL�����̎�������
//

/**
 * �_�C�A���O����������
 *
 * @return TRUE: FALSE:�t�H�[�J�X��ݒ肵��
 */
INT_PTR ReMetrics::OnInitDialog()
{
	// �e�N���X�̃_�C�A���O�������������ĂԁB
	DialogAppliBase::OnInitDialog();

	HICON hIcon;

    hIcon = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDC_MYICON), IMAGE_ICON, 16, 16, 0);
    SendMessage(this->hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);

	UpdateData(false);

	return (INT_PTR)FALSE;
}

/**
 * �_�C�A���O�R���g���[���ƃI�u�W�F�N�g�̓��e�̓��������B
 *
 * @param toObj true:�R���g���[�����I�u�W�F�N�g false:�I�u�W�F�N�g���R���g���[��
 */
void ReMetrics::UpdateData(bool toObj)
{
	// �����Ƀ_�C�A���O�̃R���g���[���Ɠ�������郁���o�ϐ����L�q���܂��B
	DDX_Text(toObj,IDC_EDIT_BORDER, borderWidth);
	DDX_Text(toObj,IDC_EDIT_TITLE_WIDTH, titleWidth);
	DDX_Text(toObj,IDC_EDIT_TITLE_HEIGHT, titleHeight);
	DDX_Text(toObj,IDC_EDIT_SCROLL_WIDTH, scrollWidth);
	DDX_Text(toObj,IDC_EDIT_SCROLL_HEIGHT, scrollHeight);
	DDX_Text(toObj,IDC_EDIT_PALETTE_WIDTH, paletteWidth);
	DDX_Text(toObj,IDC_EDIT_PALETTE_HEIGHT, paletteHeight);
	DDX_Text(toObj,IDC_EDIT_MENU_WIDTH, menuWidth);
	DDX_Text(toObj,IDC_EDIT_MENU_HEIGHT, menuHeight);
	DDX_Text(toObj,IDC_EDIT_PADDING, padding);
}

INT_PTR ReMetrics::OnCommand(WPARAM wParam)
{
	switch (LOWORD(wParam)) {
		case IDM_SET_2K:
			borderWidth = _T("1");
			titleWidth = _T("18");
			titleHeight = _T("18");
			scrollWidth = _T("16");
			scrollHeight = _T("16");
			paletteWidth = _T("18");
			paletteHeight = _T("18");
			menuWidth = _T("18");
			menuHeight = _T("18");
			padding = _T("0");
			UpdateData(false);
			return (INT_PTR)TRUE;
		case IDM_SET_XP:
			borderWidth = _T("1");
			titleWidth = _T("18");
			titleHeight = _T("18");
			scrollWidth = _T("16");
			scrollHeight = _T("16");
			paletteWidth = _T("12");
			paletteHeight = _T("15");
			menuWidth = _T("18");
			menuHeight = _T("18");
			padding = _T("0");
			UpdateData(false);
			return (INT_PTR)TRUE;
		case IDM_SET_XP_LUNA:
			borderWidth = _T("1");
			titleWidth = _T("25");
			titleHeight = _T("25");
			scrollWidth = _T("17");
			scrollHeight = _T("17");
			paletteWidth = _T("17");
			paletteHeight = _T("17");
			menuWidth = _T("18");
			menuHeight = _T("19");
			padding = _T("0");
			UpdateData(false);
			return (INT_PTR)TRUE;
		case IDM_SET_VISTA:
			borderWidth = _T("5");
			titleWidth = _T("33");
			titleHeight = _T("20");
			scrollWidth = _T("17");
			scrollHeight = _T("17");
			paletteWidth = _T("17");
			paletteHeight = _T("20");
			menuWidth = _T("19");
			menuHeight = _T("20");
			padding = _T("0");
			UpdateData(false);
			return (INT_PTR)TRUE;
		case IDM_SET_7_STD:
			borderWidth = _T("5");
			titleWidth = _T("35");
			titleHeight = _T("21");
			scrollWidth = _T("17");
			scrollHeight = _T("17");
			paletteWidth = _T("17");
			paletteHeight = _T("20");
			menuWidth = _T("19");
			menuHeight = _T("20");
			padding = _T("0");
			UpdateData(false);
			return (INT_PTR)TRUE;
		case IDM_SET_7:
			borderWidth = _T("5");
			titleWidth = _T("33");
			titleHeight = _T("20");
			scrollWidth = _T("17");
			scrollHeight = _T("17");
			paletteWidth = _T("20");
			paletteHeight = _T("20");
			menuWidth = _T("20");
			menuHeight = _T("20");
			padding = _T("0");
			UpdateData(false);
			return (INT_PTR)TRUE;
		case IDM_SET_8:
			borderWidth = _T("5");
			titleWidth = _T("36");
			titleHeight = _T("22");
			scrollWidth = _T("17");
			scrollHeight = _T("17");
			paletteWidth = _T("22");
			paletteHeight = _T("22");
			menuWidth = _T("19");
			menuHeight = _T("19");
			padding = _T("0");
			UpdateData(false);
			return (INT_PTR)TRUE;
		case IDOK:
		case IDM_SET:
			if (!OnBnClickedOk()) {
				return true;
			}
			break;
		case IDM_ABOUT:
			MessageBox(hWnd, 
				_T("Re-Metrics Version 1.00\n\nBy Tatsuhiko Syoji(Tatsu) 2012"),
				_T("Re-Metrics�ɂ���"),
				MB_OK | MB_ICONINFORMATION);
			return (INT_PTR)TRUE;
	}
	return BaseDialog::OnCommand(wParam);

}

bool ReMetrics::OnBnClickedOk()
{
	UpdateData(true);

	if (borderWidth.length() == 0) {
		MessageBox(hWnd, _T("�E�C���h�E�̋��E�����͂���Ă܂���B"), 
			_T("�G���["), MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	if (titleWidth.length() == 0) {
		MessageBox(hWnd, _T("�^�C�g���o�[�̕������͂���Ă܂���B"), 
			_T("�G���["), MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	if (titleHeight.length() == 0) {
		MessageBox(hWnd, _T("�^�C�g���o�[�̍��������͂���Ă܂���B"), 
			_T("�G���["), MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	if (scrollWidth.length() == 0) {
		MessageBox(hWnd, _T("�X�N���[���o�[�̕������͂���Ă܂���B"), 
			_T("�G���["), MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	if (scrollHeight.length() == 0) {
		MessageBox(hWnd, _T("�X�N���[���o�[�̍��������͂���Ă܂���B"), 
			_T("�G���["), MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	if (paletteWidth.length() == 0) {
		MessageBox(hWnd, _T("�p���b�g�̕������͂���Ă܂���B"), 
			_T("�G���["), MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	if (paletteHeight.length() == 0) {
		MessageBox(hWnd, _T("�p���b�g�̍��������͂���Ă܂���B"), 
			_T("�G���["), MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	if (menuWidth.length() == 0) {
		MessageBox(hWnd, _T("���j���[�̕������͂���Ă܂���B"), 
			_T("�G���["), MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	if (menuHeight.length() == 0) {
		MessageBox(hWnd, _T("���j���[�̍��������͂���Ă܂���B"), 
			_T("�G���["), MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	if (padding.length() == 0) {
		MessageBox(hWnd, _T("�E�C���h�E�g�����̕������͂���Ă܂���B"), 
			_T("�G���["), MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	DWORD dwver;

	dwver = GetVersion();

	FillMemory(&metrics,sizeof(NONCLIENTMETRICS),0x00);

	// �A�C�R���ȊO�̃t�H���g�����擾����B
	if (LOBYTE(dwver) > 5) {
		/* Windows Vista/7/8 */
		metrics.cbSize = sizeof(NONCLIENTMETRICS);
	} else {
		/* Windows 2000/XP */
		metrics.cbSize = sizeof(NONCLIENTMETRICS) - 4;
	}

	SystemParametersInfo(SPI_GETNONCLIENTMETRICS,
		metrics.cbSize,
		&metrics,
		0);

	metrics.iBorderWidth = _tstoi(borderWidth.c_str());
	metrics.iCaptionWidth = _tstoi(titleWidth.c_str());
	metrics.iCaptionHeight = _tstoi(titleHeight.c_str());
	metrics.iScrollWidth = _tstoi(scrollWidth.c_str());
	metrics.iScrollHeight = _tstoi(scrollHeight.c_str());
	metrics.iSmCaptionWidth = _tstoi(paletteWidth.c_str());
	metrics.iSmCaptionHeight = _tstoi(paletteHeight.c_str());
	metrics.iMenuWidth = _tstoi(menuWidth.c_str());
	metrics.iMenuHeight = _tstoi(menuHeight.c_str());
	metrics.iPaddedBorderWidth = _tstoi(padding.c_str());

	SystemParametersInfo(SPI_SETNONCLIENTMETRICS,
		metrics.cbSize,
		&metrics,
		SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);

	// �F���Đݒ肷�邱�Ƃŉ�ʂ����t���b�V������B
	DWORD btnColor;
	btnColor = GetSysColor(COLOR_BTNTEXT);

	INT colorItems[1];
	colorItems[0] = COLOR_BTNTEXT;
	COLORREF colors[1];
	colors[0] = btnColor;
	SetSysColors(1,colorItems,colors);

	return true;
}
