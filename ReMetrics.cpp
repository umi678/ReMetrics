/*
Re-Metrics (C) 2012,2013 Tatsuhiko Shoji
The sources for Re-Metrics are distributed under the MIT open source license
*/
// ReMetrics.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

#include <windows.h>
#include <commdlg.h>
#include "ReMetrics.h"

#define MAX_LOADSTRING 100

//
// ダイアログベースアプリケーションフレームワークと
// ユーザー実装のブリッジルーチン
//

// アプリケーションオブジェクト
ReMetrics *appObj;

/**
 * アプリケーションオブジェクトを作成します。
 */
DialogAppliBase *createAppli()
{
	// ここでユーザーのアプリケーションオブジェクトを作成します。
	appObj = new ReMetrics();
	return appObj;
}

/**
 * ダイアログプローシジャ
 *
 */
INT_PTR CALLBACK MainDialogProc(
  HWND hwndDlg,  // ダイアログボックスのハンドル
  UINT uMsg,     // メッセージ
  WPARAM wParam, // 最初のメッセージパラメータ
  LPARAM lParam  // 2 番目のメッセージパラメータ
  )
{
	// ユーザーアプリケーションのダイアログプローシジャに丸投げします。
	return appObj->dialogProc(hwndDlg, uMsg,wParam,lParam);
}

//
// ダイアログベースアプリケーションフレームワークの実装部
//

/**
 * アプリケーションウインドウクラスのインスタンスを生成します。
 *
 * @return アプリケーションウインドウクラスのインスタンス
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
 * アプリケーションの開始処理を実行します。
 *
 * @param lpCmdLine コマンドライン
 * @return 予備
 */
int ReMetrics::OnAppliStart(TCHAR *lpCmdLine)
{
	// この関数をオーバーライドしてアプリ固有の初期化を行います。
	// 本アプリケーションでは特に処理なし。
	return 0;
}

/**
 * ウインドウが表示されたときの処理を実行します。<br>
 * ウインドウベースアプリとインタフェースを合わせるために用意しています。
 *
 * @return 予備
 */
int ReMetrics::OnWindowShow()
{

	// この関数をオーバーライドして、初回の表示時の処理を行います。
	// このタイミングでダイアログが存在するので、ここに処理を入れることで
	// ダイアログがある状態で起動時の初期化処理を行うことができます。
	DWORD dwver;

	dwver = GetVersion();

	FillMemory(&metrics,sizeof(NONCLIENTMETRICS),0x00);

	// アイコン以外のフォント情報を取得する。
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
 * アプリケーションの終了処理を実行します。
 *
 * @return 予備
 */
int ReMetrics::OnAppliEnd()
{
	// この関数をオーバーライドしてアプリ固有の後処理を行います。
	// 本アプリケーションでは特に処理なし。
	return 0;
}

//
// ダイアログベースアプリケーションとしての
// アプリケーション固有処理の実装部分
//

/**
 * ダイアログ初期化処理
 *
 * @return TRUE: FALSE:フォーカスを設定した
 */
INT_PTR ReMetrics::OnInitDialog()
{
	// 親クラスのダイアログ初期化処理を呼ぶ。
	DialogAppliBase::OnInitDialog();

	HICON hIcon;

    hIcon = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDC_MYICON), IMAGE_ICON, 16, 16, 0);
    SendMessage(this->hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);

	UpdateData(false);

	return (INT_PTR)FALSE;
}

/**
 * ダイアログコントロールとオブジェクトの内容の同期を取る。
 *
 * @param toObj true:コントロール→オブジェクト false:オブジェクト→コントロール
 */
void ReMetrics::UpdateData(bool toObj)
{
	// ここにダイアログのコントロールと同期を取るメンバ変数を記述します。
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
				_T("Re-Metrics Version 1.01\n\nBy Tatsuhiko Syoji(Tatsu) 2012,2013"),
				_T("Re-Metricsについて"),
				MB_OK | MB_ICONINFORMATION);
			return (INT_PTR)TRUE;
	}
	return BaseDialog::OnCommand(wParam);

}

bool ReMetrics::OnBnClickedOk()
{
	UpdateData(true);

	if (borderWidth.length() == 0) {
		MessageBox(hWnd, _T("ウインドウの境界が入力されてません。"), 
			_T("エラー"), MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	if (titleWidth.length() == 0) {
		MessageBox(hWnd, _T("タイトルバーの幅が入力されてません。"), 
			_T("エラー"), MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	if (titleHeight.length() == 0) {
		MessageBox(hWnd, _T("タイトルバーの高さが入力されてません。"), 
			_T("エラー"), MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	if (scrollWidth.length() == 0) {
		MessageBox(hWnd, _T("スクロールバーの幅が入力されてません。"), 
			_T("エラー"), MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	if (scrollHeight.length() == 0) {
		MessageBox(hWnd, _T("スクロールバーの高さが入力されてません。"), 
			_T("エラー"), MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	if (paletteWidth.length() == 0) {
		MessageBox(hWnd, _T("パレットの幅が入力されてません。"), 
			_T("エラー"), MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	if (paletteHeight.length() == 0) {
		MessageBox(hWnd, _T("パレットの高さが入力されてません。"), 
			_T("エラー"), MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	if (menuWidth.length() == 0) {
		MessageBox(hWnd, _T("メニューの幅が入力されてません。"), 
			_T("エラー"), MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	if (menuHeight.length() == 0) {
		MessageBox(hWnd, _T("メニューの高さが入力されてません。"), 
			_T("エラー"), MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	if (padding.length() == 0) {
		MessageBox(hWnd, _T("ウインドウ枠内部の幅が入力されてません。"), 
			_T("エラー"), MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	DWORD dwver;

	dwver = GetVersion();

	FillMemory(&metrics,sizeof(NONCLIENTMETRICS),0x00);

	// アイコン以外のフォント情報を取得する。
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

	// 色を再設定することで画面をリフレッシュする。
	DWORD btnColor;
	btnColor = GetSysColor(COLOR_BTNTEXT);

	INT colorItems[1];
	colorItems[0] = COLOR_BTNTEXT;
	COLORREF colors[1];
	colors[0] = btnColor;
	SetSysColors(1,colorItems,colors);

	return true;
}
