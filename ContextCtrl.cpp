/*! @file
	@brief メインのコンテキストメニューの管理します
	このファイルは ContextCtrl.cpp です。
	@author	SikigamiHNQ
	@date	2011/11/07
*/

/*
Orinrin Editor : AsciiArt Story Editor for Japanese Only
Copyright (C) 2011 - 2013 Orinrin/SikigamiHNQ

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with this program.
If not, see <http://www.gnu.org/licenses/>.
*/
//-------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "OrinrinEditor.h"
//-------------------------------------------------------------------------------------------------

//	ユーザ定義とか枠とかは、サブメニュー用のダミーアイテムを用意する

typedef struct tagCONTEXTITEM
{
	TCHAR	atString[MIN_STRING];		//!<	表示する文字列
	UINT	dCommandoID;				//!<	コマンドＩＤ・0でセパレータ

} CONTEXTITEM, *LPCONTEXTITEM;
//-------------------------------------------------------------------------------------------------


//

//메뉴 목록 수정됨
CONST static CONTEXTITEM	gstContextItem[] =
{
        {  TEXT("- 구분선 -"),		    			    0						},
     	{  TEXT("새 파일"),	/*ファイル*/		        IDM_NEWFILE				},
    	{  TEXT("불러오기"),					        IDM_OPEN				},
		{  TEXT("저장하기"),						    IDM_OVERWRITESAVE		},
		{  TEXT("다른 이름으로 저장하기"),			    IDM_RENAMESAVE			},
		{  TEXT("이미지 파일 내보내기"),			    IDM_IMAGE_SAVE			},
    	{  TEXT("환경설정"),						    IDM_GENERAL_OPTION		},
		{  TEXT("실행 취소"),	/*編集*/			    IDM_UNDO				},
		{  TEXT("다시 실행"),						    IDM_REDO				},
		{  TEXT("잘라내기"),						    IDM_CUT					},
    	{  TEXT("복사하기"),	                	    IDM_COPY				},
		{  TEXT("유니코드를 코드 모양으로 복사"),       IDM_SJISCOPY			},
		{  TEXT("AA 전체를 코드 모양으로 복사"),        IDM_SJISCOPY_ALL		},
		{  TEXT("붙여넣기"),				    		IDM_PASTE				},
		{  TEXT("삭제"),						    	IDM_DELETE				},
    	{  TEXT("전체 선택"),					    	IDM_ALLSEL				},
		{  TEXT("직사각형 모양 선택"),			    	IDM_SQSELECT			},
		{  TEXT("직사각형 모양 붙여넣기"),		    	IDM_SQUARE_PASTE		},
		{  TEXT("레이어 박스"),				        	IDM_LAYERBOX			},
		{  TEXT("분할 선택 모드"),				    	IDM_EXTRACTION_MODE		},
    	{  TEXT("커서를 기준으로 새 페이지 분할"),   	IDM_PAGEL_DIVIDE		},
		{  TEXT("선택 범위로 페이지 이름 붙이기"),	    IDM_PAGENAME_SELASSIGN	},
		{  TEXT("유니코드 공백"),	/*挿入*/		        IDM_MN_UNISPACE			},//サブメニューダミー
		{  TEXT(" 1도트 공백"),					        IDM_IN_01SPACE			},
    	{  TEXT(" 2도트 공백"),				        	IDM_IN_02SPACE			},
		{  TEXT(" 3도트 공백"),				        	IDM_IN_03SPACE			},
		{  TEXT(" 4도트 공백"),				         	IDM_IN_04SPACE			},
		{  TEXT(" 5도트 공백"),				        	IDM_IN_05SPACE			},
		{  TEXT(" 8도트 공백"),				        	IDM_IN_08SPACE			},
    	{  TEXT("10도트 공백"),				        	IDM_IN_10SPACE			},
		{  TEXT("16도트 공백"),				        	IDM_IN_16SPACE			},
		{  TEXT("색상 코드 입력"),				    	IDM_MN_COLOUR_SEL		},//サブメニューダミー
		{  TEXT("스포(투명)"),				    		IDM_INSTAG_WHITE		},
        {  TEXT("스포 닫기 태그"),			    		IDM_INSTAG_CLOSPO		},
		{  TEXT("파란색"),					    		IDM_INSTAG_BLUE			},
    	{  TEXT("검은색"),					    		IDM_INSTAG_BLACK		},
		{  TEXT("붉은색"),						    	IDM_INSTAG_RED			},
		{  TEXT("초록색"),						    	IDM_INSTAG_GREEN		},
        {  TEXT("컬러 닫기 태그"),				    	IDM_INSTAG_CLOCLR		},
		{  TEXT("말풍선 입력"),				    		IDM_MN_INSFRAME_SEL		},//サブメニューダミー
        {  TEXT("말풍선 편집"),						    IDM_INSFRAME_EDIT		},
    	{  TEXT("말풍선 박스"),					        IDM_FRMINSBOX_OPEN		},
		{  TEXT("말풍선 1"),					    	IDM_INSFRAME_ALPHA		},
    	{  TEXT("말풍선 2"),					    	IDM_INSFRAME_BRAVO		},
		{  TEXT("말풍선 3"),						    IDM_INSFRAME_CHARLIE	},
		{  TEXT("말풍선 4"),					    	IDM_INSFRAME_DELTA		},
		{  TEXT("말풍선 5"),						    IDM_INSFRAME_ECHO		},
		{  TEXT("말풍선 6"),						    IDM_INSFRAME_FOXTROT	},
    	{  TEXT("말풍선 7"),					    	IDM_INSFRAME_GOLF		},
		{  TEXT("말풍선 8"),						    IDM_INSFRAME_HOTEL		},
		{  TEXT("말풍선 9"),						    IDM_INSFRAME_INDIA		},
		{  TEXT("말풍선 10"),						    IDM_INSFRAME_JULIETTE	},
		{  TEXT("말풍선 11"),					    	IDM_INSFRAME_KILO		},
    	{  TEXT("말풍선 12"),					    	IDM_INSFRAME_LIMA		},
		{  TEXT("말풍선 13"),					    	IDM_INSFRAME_MIKE		},
		{  TEXT("말풍선 14"),						    IDM_INSFRAME_NOVEMBER	},
		{  TEXT("말풍선 15"),					    	IDM_INSFRAME_OSCAR		},
		{  TEXT("말풍선 16"),						    IDM_INSFRAME_PAPA		},
    	{  TEXT("말풍선 17"),						    IDM_INSFRAME_QUEBEC		},
		{  TEXT("말풍선 18"),						    IDM_INSFRAME_ROMEO		},
		{  TEXT("말풍선 19"),						    IDM_INSFRAME_SIERRA		},
		{  TEXT("말풍선 20"),						    IDM_INSFRAME_TANGO		},
		{  TEXT("유저 제작 템플릿"),				    IDM_MN_USER_REFS		},//サブメニューダミー
		{  TEXT("유저 제작 템플릿 1"),		          	IDM_USER_ITEM_ALPHA		},
    	{  TEXT("유저 제작 템플릿 2"),		         	IDM_USER_ITEM_BRAVO		},
		{  TEXT("유저 제작 템플릿 3"),			        IDM_USER_ITEM_CHARLIE	},
		{  TEXT("유저 제작 템플릿 4"),    			    IDM_USER_ITEM_DELTA		},
		{  TEXT("유저 제작 템플릿 5"),	    		    IDM_USER_ITEM_ECHO		},
		{  TEXT("유저 제작 템플릿 6"),		        	IDM_USER_ITEM_FOXTROT	},
    	{  TEXT("유저 제작 템플릿 7"),			        IDM_USER_ITEM_GOLF		},
		{  TEXT("유저 제작 템플릿 8"),    		    	IDM_USER_ITEM_HOTEL		},
		{  TEXT("유저 제작 템플릿 9"),	    	    	IDM_USER_ITEM_INDIA		},
		{  TEXT("유저 제작 템플릿 10"),		           	IDM_USER_ITEM_JULIETTE	},
		{  TEXT("유저 제작 템플릿 11"),			        IDM_USER_ITEM_KILO		},
    	{  TEXT("유저 제작 템플릿 12"),   		    	IDM_USER_ITEM_LIMA		},
		{  TEXT("유저 제작 템플릿 13"),	    	    	IDM_USER_ITEM_MIKE		},
		{  TEXT("유저 제작 템플릿 14"),		        	IDM_USER_ITEM_NOVEMBER	},
		{  TEXT("유저 제작 템플릿 15"),			        IDM_USER_ITEM_OSCAR		},
		{  TEXT("유저 제작 템플릿 16"),   		    	IDM_USER_ITEM_PAPA		},
    	{  TEXT("문서에 일련번호 넣기"),	    		IDM_PAGENUM_DLG_OPEN	},
		{  TEXT("우측에 직선 추가"),	/*整形*/ 	    IDM_RIGHT_GUIDE_SET		},
		{  TEXT("좌측 공백을 오른쪽으로 밀기"),		    IDM_INS_TOPSPACE		},
		{  TEXT("좌측 공백을 왼쪽으로 당기기"),	    	IDM_DEL_TOPSPACE		},
    	{  TEXT("줄 끝에 남는 공백 제거"),		    	IDM_DEL_LASTSPACE		},
		{  TEXT("줄 끝 마지막 문자 제거"),		        IDM_DEL_LASTLETTER		},
		{  TEXT("선택 범위 공백으로 채우기"),		    IDM_FILL_SPACE			},
		{  TEXT("빈 공간을 공백으로 채우기"),	    	IDM_FILL_ZENSP			},
		{  TEXT("첫 반각 공백을 유니코드로 변환"),      IDM_HEADHALF_EXCHANGE	},
    	{  TEXT("좌우 반전"),					    	IDM_MIRROR_INVERSE		},
		{  TEXT("상하 반전"),					    	IDM_UPSET_INVERSE		},
		{  TEXT("AA 전체를 오른쪽으로 밀기"),	    	IDM_RIGHT_SLIDE			},
		{  TEXT("공백을 1도트 늘리기"),			    	IDM_INCREMENT_DOT		},
		{  TEXT("공백을 1도트 줄이기"),			    	IDM_DECREMENT_DOT		},
    	{  TEXT("AA 전체를 오른쪽으로 1도트 밀기"),    	IDM_INCR_DOT_LINES		},
        {  TEXT("AA 전체를 왼쪽으로 1도트 당기기"),	    IDM_DECR_DOT_LINES		},
		{  TEXT("커서를 기준으로 왼쪽으로 당기기"),   	IDM_DOT_SPLIT_RIGHT		},
		{  TEXT("커서를 기준으로 오른쪽으로 밀기"),   	IDM_DOT_SPLIT_LEFT		},
		{  TEXT("조정 기준 위치 잠그기"),				IDM_DOTDIFF_LOCK		},
    	{  TEXT("커서 우측 공백 전부 지우기"),			IDM_DOTDIFF_ADJT		},
		{  TEXT("공백 문자 표시"),	/*表示*/		    IDM_SPACE_VIEW_TOGGLE	},
		{  TEXT("그리드 표시"),			              	IDM_GRID_VIEW_TOGGLE	},
		{  TEXT("우측 가이드라인 표시"),			    IDM_RIGHT_RULER_TOGGLE	},
    	{  TEXT("하단 가이드라인 표시"),			   	IDM_UNDER_RULER_TOGGLE	},
		{  TEXT("페이지 목록 표시"),			     	IDM_PAGELIST_VIEW		},
		{  TEXT("AA 팔레트 표시"),		             	IDM_LINE_TEMPLATE		},
		{  TEXT("브러시 팔레트 표시"),		    	    IDM_BRUSH_PALETTE		},
    	{  TEXT("유니코드 문자표 열기"),			    IDM_UNI_PALETTE			},
		{  TEXT("트레이싱 모드"),					    IDM_TRACE_MODE_ON		},
        {  TEXT("미리보기"),						    IDM_ON_PREVIEW          },
		{  TEXT("선택한 페이지를 복제"),		        IDM_PAGEL_DUPLICATE		},
		{  TEXT("선택한 페이지를 삭제"),	           	IDM_PAGEL_DELETE		},
    	{  TEXT("다음 페이지와 결합"),			    	IDM_PAGEL_COMBINE		},
		{  TEXT("새 페이지 삽입"),		 	        	IDM_PAGEL_INSERT		},
		{  TEXT("새 페이지 추가"),			 		   	IDM_PAGEL_ADD			},
		{  TEXT("페이지를 아래로 이동"),	    		IDM_PAGEL_DOWNSINK		},
		{  TEXT("페이지를 위로 이동"),			    	IDM_PAGEL_UPFLOW		},
    	{  TEXT("페이지 이름 바꾸기"),		        	IDM_PAGEL_RENAME		},
		{  TEXT("트레이싱용 이미지 표시"),   		 	IDM_TRC_VIEWTOGGLE		},
		{  TEXT("템플릿 그룹 전환 ↑"),		         	IDM_TMPLT_GROUP_PREV	},
		{  TEXT("템플릿 그룹 전환 ↓"),		 		   	IDM_TMPLT_GROUP_NEXT	},
		{  TEXT("윈도우 포커스 전환 ↑"),		    	IDM_WINDOW_CHANGE		},
    	{  TEXT("윈도우 포커스 전환 ↓"),		    	IDM_WINDOW_CHG_RVRS		},
		{  TEXT("파일 닫기"),					    	IDM_FILE_CLOSE			},
		{  TEXT("파일 전환 ↑"),					    IDM_FILE_PREV			},
		{  TEXT("파일 전환 ↓"),					    IDM_FILE_NEXT			},
		{  TEXT("이전 페이지로"),				    	IDM_PAGE_PREV			},
    	{  TEXT("다음 페이지로"),				    	IDM_PAGE_NEXT			},
		{  TEXT("현재 화면 새로고침"),			    	IDM_NOW_PAGE_REFRESH	},
		{  TEXT("찾기"),		 			         	IDM_FIND_DLG_OPEN		}, /* 미실장 */
    	{  TEXT("검색 설정 초기화"),					IDM_FIND_HIGHLIGHT_OFF	}, /* 미실장 */
		{  TEXT("다음 찾기"),				    		IDM_FIND_JUMP_NEXT		}, /* 미실장 */
		{  TEXT("이전 찾기"),					    	IDM_FIND_JUMP_PREV		}, /* 미실장 */
		{  TEXT("검색 대상 설정"),						IDM_FIND_TARGET_SET		}, /* 미실장 */
};

#define ALL_ITEMS	 117	//	右クリ用　０インデックス
#define FULL_ITEMS	 145	//	全アイテム

//	右クリ用サブアイテム・位置調整忘れないように
#define CTS_UNISPACE	24
#define CTS_COLOURINS	33
#define CTS_FRAMEINS	39
#define CTS_USERITEM	64

//	サブ展開するアイテムに注意セヨ・コンテキストメニューとアクセルキー

//	キーバインド・メニューに入ってない機能に注意

//初期設定
#define DEF_ITEMS	32
const static UINT	gadDefItem[] =
{
	IDM_CUT,				//	切り取り
	IDM_COPY,				//	Unicodeコピー
	IDM_PASTE,				//	貼付
	IDM_ALLSEL,				//	全選択
	0,
	IDM_COPY_TO_DRAUGHT,	//	選択範囲をドラフトボードへ
	0,
	IDM_SJISCOPY,			//	SJISコピー
	IDM_SJISCOPY_ALL,		//	全体をSJISコピー
	0,
	IDM_SQSELECT,			//	矩形選択
	0,
	IDM_LAYERBOX,			//	レイヤボックス
	IDM_FRMINSBOX_OPEN,		//	枠挿入ボックス
	IDM_MOZI_SCR_OPEN,		//	文字ＡＡ変換ボックス
	0,
	IDM_RIGHT_GUIDE_SET,	//	右揃え線
	IDM_INS_TOPSPACE,		//	行頭に全角空白追加
	IDM_DEL_TOPSPACE,		//	行頭空白削除
	IDM_DEL_LASTSPACE,		//	行末空白削除
	IDM_DEL_LASTLETTER,		//	行末文字削除
	IDM_FILL_SPACE,			//	選択範囲を空白にする
	IDM_RIGHT_SLIDE,		//	右に寄せる
	0,
	IDM_INCR_DOT_LINES,		//	全体を１ドット右へ
	IDM_DECR_DOT_LINES,		//	全体を１ドット左へ
	0,
	IDM_SPACE_VIEW_TOGGLE,	//	空白を表示	
	IDM_GRID_VIEW_TOGGLE,	//	グリッド線を表示
	IDM_RIGHT_RULER_TOGGLE,	//	右ガイド線を表示
	0,
	IDM_PAGEL_DIVIDE		//	次の行以降を新頁に分割
};
//-------------------------------------------------------------------------------------------------








static HINSTANCE	ghInst;
static TCHAR		gatCntxIni[MAX_PATH];	//!<	

static HMENU	ghPopupMenu;	
static HMENU	ghUniSpMenu;
static HMENU	ghColourMenu;
static HMENU	ghFrameMenu;
static HMENU	ghUsrDefMenu;

static vector<CONTEXTITEM>	gvcCntxItem;
typedef vector<CONTEXTITEM>::iterator	CTXI_VITR;

static list<CONTEXTITEM>	gltCntxEdit;
typedef list<CONTEXTITEM>::iterator	CTXI_LITR;
//-------------------------------------------------------------------------------------------------

VOID	CntxEditBuild( VOID );

INT_PTR	CALLBACK CntxEditDlgProc( HWND, UINT, WPARAM, LPARAM );

VOID	CntxDlgLvInit( HWND );
VOID	CntxDlgAllListUp( HWND );
VOID	CntxDlgBuildListUp( HWND );

VOID	CntxDlgItemAdd( HWND );
VOID	CntxDlgItemDel( HWND );
VOID	CntxDlgItemSpinUp( HWND );
VOID	CntxDlgItemSpinDown( HWND );


INT_PTR	CALLBACK AccelKeyDlgProc( HWND, UINT, WPARAM, LPARAM );
INT_PTR	AccelKeyNotify( HWND, INT, LPNMHDR, list<ACCEL> * );

HRESULT	AccelKeyBindExistCheck( HWND, LPACCEL, list<ACCEL> * );
HRESULT	AccelKeyBindListMod( HWND, INT, LPACCEL, list<ACCEL> * );
HRESULT	AccelKeySettingReset( HWND, list<ACCEL> * );
HRESULT	AccelKeyListOutput( HWND );
HRESULT	AccelKeyBindString( LPACCEL, LPTSTR, UINT_PTR );
VOID	AccelKeyListInit( HWND, list<ACCEL> * );
BYTE	AccelHotModExchange( BYTE, BOOLEAN );
HRESULT	AccelKeyTableSave( list<ACCEL> * );



//-------------------------------------------------------------------------------------------------

/*!
	起動時初期化・INIディレクトリ格納とか初期生成とか
	@param[in]	ptCurrent	基準ディレクトリ
	@param[in]	hInstance	このアプリの実存
	@return		HRESULT		終了状態コード
*/
HRESULT CntxEditInitialise( LPTSTR ptCurrent, HINSTANCE hInstance )
{
	UINT	dCount, cid;
	UINT	ams, ims;
	TCHAR	atKeyName[MIN_STRING];



	if( !(ptCurrent) || !(hInstance) )
	{
		if( ghPopupMenu ){	DestroyMenu( ghPopupMenu  );	}
		if( ghUniSpMenu ){	DestroyMenu( ghUniSpMenu  );	}
		if( ghColourMenu ){	DestroyMenu( ghColourMenu );	}
		if( ghFrameMenu ){	DestroyMenu( ghFrameMenu  );	}
		if( ghUsrDefMenu ){	DestroyMenu( ghUsrDefMenu );	}

		return S_OK;
	}



	ghInst = hInstance;

	StringCchCopy( gatCntxIni, MAX_PATH, ptCurrent );
	PathAppend( gatCntxIni, MZCX_INI_FILE );


	gvcCntxItem.clear();

	//	初期状態
	dCount = GetPrivateProfileInt( TEXT("Context"), TEXT("Count"), 0, gatCntxIni );
	if( 1 <= dCount )	//	データ有り
	{
		for( ims = 0; dCount > ims; ims++ )
		{
			StringCchPrintf( atKeyName, MIN_STRING, TEXT("CmdID%u"), ims );
			cid = GetPrivateProfileInt( TEXT("Context"), atKeyName, 0, gatCntxIni );

			for( ams = 0; ALL_ITEMS > ams; ams++ )
			{
				if( cid == gstContextItem[ams].dCommandoID )
				{
					gvcCntxItem.push_back( gstContextItem[ams] );
					break;
				}
			}
		}
	}
	else	//	データ無しならデフォメニューを構築
	{
		for( ims = 0; DEF_ITEMS > ims; ims++ )
		{
			for( ams = 0; ALL_ITEMS > ams; ams++ )
			{
				if( gadDefItem[ims] == gstContextItem[ams].dCommandoID )
				{
					gvcCntxItem.push_back( gstContextItem[ams] );
					break;
				}
			}
		}
	}

	CntxEditBuild(  );

	return S_OK;
}
//-------------------------------------------------------------------------------------------------

/*!
	できあがってるコンテキストメニューを外部で使う
*/
HMENU CntxMenuGet( VOID )
{
	return ghPopupMenu;
}
//-------------------------------------------------------------------------------------------------

/*!
	コンテキストメニューを組み立てる。
*/
VOID CntxEditBuild( VOID )
{
	UINT	d, e, num;
	TCHAR	atItem[MAX_STRING], atKey[MIN_STRING], atBuffer[SUB_STRING];
	CTXI_VITR	itMnItm;

	if( ghPopupMenu ){	DestroyMenu( ghPopupMenu  );	}	ghPopupMenu  = NULL;
	if( ghUniSpMenu ){	DestroyMenu( ghUniSpMenu  );	}	ghUniSpMenu  = NULL;
	if( ghColourMenu ){	DestroyMenu( ghColourMenu );	}	ghColourMenu = NULL;
	if( ghFrameMenu ){	DestroyMenu( ghFrameMenu  );	}	ghFrameMenu  = NULL;
	if( ghUsrDefMenu ){	DestroyMenu( ghUsrDefMenu );	}	ghUsrDefMenu = NULL;

	ghPopupMenu = CreatePopupMenu(  );

	e = 0;
	for( itMnItm = gvcCntxItem.begin(); gvcCntxItem.end() != itMnItm; itMnItm++ )
	{
		if( 0 >= itMnItm->dCommandoID )
		{
			AppendMenu( ghPopupMenu, MF_SEPARATOR, 0, NULL );
		}
		else
		{
			ZeroMemory( atBuffer, sizeof(atBuffer) );
			StringCchCopy( atItem, MAX_STRING, itMnItm->atString );	//	先に記録

			if( IDM_INSFRAME_ALPHA <= itMnItm->dCommandoID && itMnItm->dCommandoID <= IDM_INSFRAME_TANGO )
			{	//	枠名称										//	IDM_INSFRAME_ZULU
				num = itMnItm->dCommandoID - IDM_INSFRAME_ALPHA;
				FrameNameLoad( num, atBuffer, SUB_STRING );
				StringCchPrintf( atItem, MAX_STRING, TEXT("말풍선：%s"), atBuffer );
			}
			else if( IDM_USER_ITEM_ALPHA <= itMnItm->dCommandoID && itMnItm->dCommandoID <= IDM_USER_ITEM_PAPA )
			{	//	ユーザアイテム名称
				num = itMnItm->dCommandoID - IDM_USER_ITEM_ALPHA;
				UserDefItemNameget( num, atBuffer, SUB_STRING );
				StringCchPrintf( atItem, MAX_STRING, TEXT("템플릿：%s"), atBuffer );
			}
			else
			{
				//	何も無い
			}

			if( 26 > e )
			{
				StringCchPrintf( atKey, MIN_STRING, TEXT("(&%c)"), 'A' + e );
				StringCchCat( atItem, MAX_STRING, atKey );
				e++;
			}

			switch( itMnItm->dCommandoID )
			{
				default:	AppendMenu( ghPopupMenu, MF_STRING, itMnItm->dCommandoID, atItem );	break;

				case IDM_MN_UNISPACE:
					ghUniSpMenu = CreatePopupMenu(  );
					for( d = 0; 8 > d; d++ ){	AppendMenu( ghUniSpMenu, MF_STRING, gstContextItem[CTS_UNISPACE+d].dCommandoID, gstContextItem[CTS_UNISPACE+d].atString );	}
					AppendMenu( ghPopupMenu, MF_POPUP, (UINT_PTR)ghUniSpMenu, atItem );
					break;

				case IDM_MN_COLOUR_SEL:
					ghColourMenu = CreatePopupMenu(  );
					for( d = 0; 5 > d; d++ ){	AppendMenu( ghColourMenu, MF_STRING, gstContextItem[CTS_COLOURINS+d].dCommandoID, gstContextItem[CTS_COLOURINS+d].atString );	}
					AppendMenu( ghPopupMenu, MF_POPUP, (UINT_PTR)ghColourMenu, atItem );
					break;

				case IDM_MN_INSFRAME_SEL:
					ghFrameMenu = CreatePopupMenu(  );
					for( d = 0; FRAME_MAX > d; d++ )
					{
					//	FrameNameLoad( d, atBuffer, SUB_STRING );
						AppendMenu( ghFrameMenu, MF_STRING, gstContextItem[CTS_FRAMEINS+d].dCommandoID, gstContextItem[CTS_FRAMEINS+d].atString );
					}
					FrameNameModifyPopUp( ghFrameMenu, 1 );
					AppendMenu( ghPopupMenu, MF_POPUP, (UINT_PTR)ghFrameMenu, atItem );
					break;

				case IDM_MN_USER_REFS:
					ghUsrDefMenu = CreatePopupMenu(  );
					UserDefMenuWrite( ghUsrDefMenu, 1 );
					AppendMenu( ghPopupMenu, MF_POPUP, (UINT_PTR)ghUsrDefMenu, atItem );
					break;
			}
		}
	}

	return;
}
//-------------------------------------------------------------------------------------------------

/*!
	編集ダイヤログ開く
	@param[in]	hWnd	ウインドウハンドル
	@return		HRESULT	終了状態コード
*/
HRESULT CntxEditDlgOpen( HWND hWnd )
{
	INT_PTR	iRslt, i;
	TCHAR	atKeyName[MIN_STRING], atBuff[MIN_STRING];
	CTXI_LITR	itEdit;

	iRslt = DialogBoxParam( ghInst, MAKEINTRESOURCE(IDD_CONTEXT_ITEM_DLG), hWnd, CntxEditDlgProc, 0 );
	if( IDOK == iRslt )
	{
		//	一旦セクションを空にする
		ZeroMemory( atBuff, sizeof(atBuff) );
		WritePrivateProfileSection( TEXT("Context"), atBuff, gatCntxIni );

		gvcCntxItem.clear();	i = 0;
		for( itEdit = gltCntxEdit.begin(); gltCntxEdit.end() != itEdit; itEdit++ )
		{
			StringCchPrintf( atKeyName, MIN_STRING, TEXT("CmdID%d"), i );
			StringCchPrintf( atBuff, MIN_STRING, TEXT("%u"), itEdit->dCommandoID );
			WritePrivateProfileString( TEXT("Context"), atKeyName, atBuff, gatCntxIni );

			gvcCntxItem.push_back( *itEdit );
			i++;
		}

		StringCchPrintf( atBuff, MIN_STRING, TEXT("%u"), i );
		WritePrivateProfileString( TEXT("Context"), TEXT("Count"), atBuff, gatCntxIni );

		CntxEditBuild(  );

		return S_OK;
	}

	return E_ABORT;
}
//-------------------------------------------------------------------------------------------------

/*!
	編集ダイヤログボックスのメセージハンドラだってばよ
	@param[in]	hDlg	ダイヤログハンドル
	@param[in]	message	ウインドウメッセージの識別番号
	@param[in]	wParam	追加の情報１
	@param[in]	lParam	追加の情報２
	@retval 0	メッセージは処理していない
	@retval no0	なんか処理された
*/
INT_PTR CALLBACK CntxEditDlgProc( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam )
{
	INT		id;
	HWND	hWndCtl;
	UINT	codeNotify;

	CTXI_VITR	itMnItm;


	switch( message )
	{
		case WM_INITDIALOG:
			gltCntxEdit.clear();
			for( itMnItm = gvcCntxItem.begin(); gvcCntxItem.end() != itMnItm; itMnItm++ ){	gltCntxEdit.push_back( *itMnItm );	}
			CntxDlgLvInit( hDlg );
			CntxDlgAllListUp( hDlg );
			CntxDlgBuildListUp( hDlg );
			return (INT_PTR)TRUE;

		case WM_COMMAND:
			id         = LOWORD(wParam);	//	メッセージを発生させた子ウインドウの識別子
			hWndCtl    = (HWND)lParam;		//	メッセージを発生させた子ウインドウのハンドル
			codeNotify = HIWORD(wParam);	//	通知メッセージ
			switch( id )
			{
				case IDOK:		EndDialog( hDlg, IDOK );		return (INT_PTR)TRUE;
				case IDCANCEL:	EndDialog( hDlg, IDCANCEL );	return (INT_PTR)TRUE;

				case IDB_MENUITEM_ADD:		CntxDlgItemAdd( hDlg );	return (INT_PTR)TRUE;
				case IDB_MENUITEM_DEL:		CntxDlgItemDel( hDlg );	return (INT_PTR)TRUE;

				case IDB_MENUITEM_SPINUP:	CntxDlgItemSpinUp( hDlg );		return (INT_PTR)TRUE;
				case IDB_MENUITEM_SPINDOWN:	CntxDlgItemSpinDown( hDlg );	return (INT_PTR)TRUE;

				default:	break;
			}
			break;
	}

	return (INT_PTR)FALSE;
}
//-------------------------------------------------------------------------------------------------

/*!
	アイテムのリストビュー作成
	@param[in]	hDlg	ダイヤログハンドル
*/
VOID CntxDlgLvInit( HWND hDlg )
{
	HWND	hLvWnd;
	LVCOLUMN	stLvColm;
	RECT	rect;


	hLvWnd = GetDlgItem( hDlg, IDLV_MENU_ALLITEM );
	GetClientRect( hLvWnd, &rect );

	ListView_SetExtendedListViewStyle( hLvWnd, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP );

	ZeroMemory( &stLvColm, sizeof(LVCOLUMN) );
	stLvColm.mask     = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	stLvColm.fmt      = LVCFMT_LEFT;
	stLvColm.iSubItem = 0;

	stLvColm.pszText  = TEXT("메뉴 항목");
	stLvColm.cx       = rect.right - 23;
	ListView_InsertColumn( hLvWnd, 0, &stLvColm );


	hLvWnd = GetDlgItem( hDlg, IDLV_MENU_BUILDX );
	GetClientRect( hLvWnd, &rect );

	ListView_SetExtendedListViewStyle( hLvWnd, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP );

	stLvColm.cx       = rect.right - 23;
	ListView_InsertColumn( hLvWnd, 0, &stLvColm );

}
//-------------------------------------------------------------------------------------------------

/*!
	全アイテムをリストビューにブッこむ
	@param[in]	hDlg	ダイヤログハンドル
*/
VOID CntxDlgAllListUp( HWND hDlg )
{
	HWND	hLvWnd;
	UINT	d;
	LVITEM	stLvi;
	TCHAR	atItem[SUB_STRING];


	hLvWnd = GetDlgItem( hDlg, IDLV_MENU_ALLITEM );

	ListView_DeleteAllItems( hLvWnd );

	ZeroMemory( &stLvi, sizeof(stLvi) );
	stLvi.mask    = LVIF_TEXT;
	stLvi.pszText = atItem;

	for( d = 0; ALL_ITEMS > d; d++ )
	{
		StringCchCopy( atItem, SUB_STRING, gstContextItem[d].atString );

		if( IDM_MN_UNISPACE == gstContextItem[d].dCommandoID || 
		IDM_MN_COLOUR_SEL   == gstContextItem[d].dCommandoID || 
		IDM_MN_INSFRAME_SEL == gstContextItem[d].dCommandoID || 
		IDM_MN_USER_REFS    == gstContextItem[d].dCommandoID )
		{
            StringCchCat(atItem, SUB_STRING, TEXT(" (하위 메뉴 포함)"));
		}

		stLvi.iItem = d;
		ListView_InsertItem( hLvWnd, &stLvi );
	}
}
//-------------------------------------------------------------------------------------------------

/*!
	メニュー構成をリストビューに表示
	@param[in]	hDlg	ダイヤログハンドル
*/
VOID CntxDlgBuildListUp( HWND hDlg )
{
	HWND	hLvWnd;
	UINT	d;
	LVITEM	stLvi;
	TCHAR	atItem[SUB_STRING];

	CTXI_LITR	itMnItm;


	hLvWnd = GetDlgItem( hDlg, IDLV_MENU_BUILDX );

	ListView_DeleteAllItems( hLvWnd );

	ZeroMemory( &stLvi, sizeof(stLvi) );
	stLvi.mask    = LVIF_TEXT;
	stLvi.pszText = atItem;

	for( itMnItm = gltCntxEdit.begin(), d = 0; gltCntxEdit.end() != itMnItm; itMnItm++, d++ )
	{
		stLvi.iItem = d;
		if( 0 >= itMnItm->dCommandoID )
		{
			StringCchCopy( atItem, SUB_STRING, TEXT("---------------") );
		}
		else
		{
			StringCchCopy( atItem, SUB_STRING, itMnItm->atString );

			if( IDM_MN_UNISPACE == itMnItm->dCommandoID || 
			IDM_MN_COLOUR_SEL   == itMnItm->dCommandoID || 
			IDM_MN_INSFRAME_SEL == itMnItm->dCommandoID || 
			IDM_MN_USER_REFS    == itMnItm->dCommandoID )
			{
				StringCchCat( atItem, SUB_STRING, TEXT("　　[＞") );
			}

		}

		ListView_InsertItem( hLvWnd, &stLvi );
	}

	return;
}
//-------------------------------------------------------------------------------------------------

/*!
	アイテムを追加
	@param[in]	hDlg	ダイヤログハンドル
*/
VOID CntxDlgItemAdd( HWND hDlg )
{
	HWND	hListWnd, hBuildWnd;
	INT		iSel, iIns, iCount;
	CTXI_LITR	itMnItm;

	hListWnd  = GetDlgItem( hDlg, IDLV_MENU_ALLITEM );
	hBuildWnd = GetDlgItem( hDlg, IDLV_MENU_BUILDX );

	//	元のほう
	iSel = ListView_GetNextItem( hListWnd, -1, LVNI_ALL | LVNI_SELECTED );
	if( 0 > iSel )	 return;	//	選択してなかったら終わり

	iCount = ListView_GetItemCount( hBuildWnd );


	//	選択したヤツの次にいれる・未選択か末尾なら末尾へ
	iIns = ListView_GetNextItem( hBuildWnd, -1, LVNI_ALL | LVNI_SELECTED );
	if( (0 > iIns) || ((iIns+1) >= iCount) ){	gltCntxEdit.push_back( gstContextItem[iSel] );	}
	else
	{
		itMnItm = gltCntxEdit.begin();
		std::advance( itMnItm, iIns+1 );
		//	イテレータの直前に入る
		gltCntxEdit.insert( itMnItm, gstContextItem[iSel] );
	}



	CntxDlgBuildListUp( hDlg );

	return;
}
//-------------------------------------------------------------------------------------------------

/*!
	アイテムを削除
	@param[in]	hDlg	ダイヤログハンドル
*/
VOID CntxDlgItemDel( HWND hDlg )
{
	HWND	hListWnd, hBuildWnd;
	INT		iSel;
	CTXI_LITR	itMnItm;

	hListWnd  = GetDlgItem( hDlg, IDLV_MENU_ALLITEM );
	hBuildWnd = GetDlgItem( hDlg, IDLV_MENU_BUILDX );

	iSel = ListView_GetNextItem( hBuildWnd, -1, LVNI_ALL | LVNI_SELECTED );
	if( 0 > iSel )	return;	//	選択してなかったら終わり

	itMnItm = gltCntxEdit.begin();
	std::advance( itMnItm, iSel );

	gltCntxEdit.erase( itMnItm );

	CntxDlgBuildListUp( hDlg );

	return;
}
//-------------------------------------------------------------------------------------------------

/*!
	アイテムを↑へ
	@param[in]	hDlg	ダイヤログハンドル
*/
VOID CntxDlgItemSpinUp( HWND hDlg )
{
	HWND	hBuildWnd;
	INT		iSel;
	CTXI_LITR	itTgtItm, itSwpItm;
	CONTEXTITEM	stItem;

	hBuildWnd = GetDlgItem( hDlg, IDLV_MENU_BUILDX );

	iSel = ListView_GetNextItem( hBuildWnd, -1, LVNI_ALL | LVNI_SELECTED );
	if( 0 >= iSel ){	 return;	}	//	選択してないか一番上なら終わり

	itTgtItm = gltCntxEdit.begin();
	std::advance( itTgtItm, iSel );
	itSwpItm = itTgtItm;
	itSwpItm--;	//	入れる先は一つ前

	StringCchCopy( stItem.atString, MIN_STRING, itTgtItm->atString );
	stItem.dCommandoID = itTgtItm->dCommandoID;

	gltCntxEdit.erase( itTgtItm );
	gltCntxEdit.insert( itSwpItm, stItem );

	CntxDlgBuildListUp( hDlg );

	ListView_SetItemState( hBuildWnd, --iSel, LVIS_SELECTED, LVIS_SELECTED );

	return;
}
//-------------------------------------------------------------------------------------------------

/*!
	アイテムを↓へ
	@param[in]	hDlg	ダイヤログハンドル
*/
VOID CntxDlgItemSpinDown( HWND hDlg )
{
	HWND	hBuildWnd;
	INT		iSel, iCount;
	CTXI_LITR	itTgtItm, itSwpItm;
	CONTEXTITEM	stItem;

	hBuildWnd = GetDlgItem( hDlg, IDLV_MENU_BUILDX );

	iSel = ListView_GetNextItem( hBuildWnd, -1, LVNI_ALL | LVNI_SELECTED );
	if( 0 > iSel )	return;	//	選択してなかったら終わり

	iCount = ListView_GetItemCount( hBuildWnd );
	if( iSel >= (iCount-1) )	 return;	//	末端なら終わり

	//	処理の位置関係に注意
	itSwpItm = gltCntxEdit.begin();
	std::advance( itSwpItm, iSel );
	itTgtItm = itSwpItm;
	itTgtItm++;	//	入れる先は一つ次

	StringCchCopy( stItem.atString, MIN_STRING, itTgtItm->atString );
	stItem.dCommandoID = itTgtItm->dCommandoID;

	gltCntxEdit.erase( itTgtItm );
	gltCntxEdit.insert( itSwpItm, stItem );

	CntxDlgBuildListUp( hDlg );

	ListView_SetItemState( hBuildWnd, ++iSel, LVIS_SELECTED, LVIS_SELECTED );

	return;
}
//-------------------------------------------------------------------------------------------------



#ifdef ACCELERATOR_EDIT
//-------------------------------------------------------------------------------------------------

//	ホットキーコントロールは、フォーカスあててキー入力すると認識する
//	登録済みのグローバルホットキーがあると、そっちが優先して動く

/*!
	アクセラレートキー編集DIALOGUEを開く
	@param[in]	hWnd		ウインドウハンドル
	@return		HRESULT		終了状態コード
*/
HRESULT AccelKeyDlgOpen( HWND hWnd )
{
	INT_PTR	iRslt;

	LPACCEL	pstAccel;
	INT	iEntry;

	iRslt = DialogBoxParam( ghInst, MAKEINTRESOURCE(IDD_ACCEL_KEY_DLG), hWnd, AccelKeyDlgProc, 0 );
	if( IDOK == iRslt )
	{
		//	アクセラハンドル書換が必要
		//	アクセラテーブル確保してメモリ構造体で確保
		pstAccel = AccelKeyTableLoadAlloc( &iEntry );
		AccelKeyTableCreate( pstAccel, iEntry );

		ToolBarInfoChange( pstAccel, iEntry );

		FREE( pstAccel );
	}

	return S_OK;
}
//-------------------------------------------------------------------------------------------------

/*!
	アクセルキー編集ダイヤログボックスのメセージハンドラだってばよ
	@param[in]	hDlg	ダイヤログハンドル
	@param[in]	message	ウインドウメッセージの識別番号
	@param[in]	wParam	追加の情報１
	@param[in]	lParam	追加の情報２
	@retval 0	メッセージは処理していない
	@retval no0	なんか処理された
*/
INT_PTR CALLBACK AccelKeyDlgProc( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam )
{
	static list<ACCEL>	cltAccel;

	INT		iAccEntry;
	LPACCEL	pstAccel;

	static  HWND	hHokyWnd;
	HWND	hLvWnd;
	LRESULT	lRslt;
	ACCEL	stAcce;
//	TCHAR	atBuffer[SUB_STRING];

	INT		i;
	INT		iItem;

	INT		id;
	HWND	hWndCtl;
	UINT	codeNotify;

//ホットキーCONTROLは、スペースが使えない

	switch( message )
	{
		case WM_INITDIALOG:
			hLvWnd = GetDlgItem( hDlg, IDLV_FUNCKEY_LIST );
			ListView_SetExtendedListViewStyle( hLvWnd, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP );

			cltAccel.clear();
			pstAccel = AccelKeyTableGetAlloc( &iAccEntry );
			//	ここで確保したアクセラはリストにして保持しておく
			for( i = 0; iAccEntry > i; i++ ){	cltAccel.push_back( pstAccel[i] );	}
			FREE( pstAccel );

			AccelKeyListInit( hDlg, &cltAccel );

			hHokyWnd = GetDlgItem( hDlg, IDHKC_FUNCKEY_INPUT );
			return (INT_PTR)TRUE;

		case WM_COMMAND:
			id         = LOWORD(wParam);	//	メッセージを発生させた子ウインドウの識別子
			hWndCtl    = (HWND)lParam;		//	メッセージを発生させた子ウインドウのハンドル
			codeNotify = HIWORD(wParam);	//	通知メッセージ
			switch( id )
			{
				case IDOK:
					AccelKeyTableSave( &cltAccel );	//	セーブ
				case IDCANCEL:
					cltAccel.clear();
					EndDialog( hDlg, id );
					return (INT_PTR)TRUE;


				case IDB_FUNCKEY_CLEAR:	//	解除
					SendMessage( hHokyWnd, HKM_SETHOTKEY, 0, 0 );
					iItem = WndTagGet( hHokyWnd );
					AccelKeyBindListMod( hDlg, iItem, NULL, &cltAccel );
					return (INT_PTR)TRUE;


				case IDB_FUNCKEY_SET:	//	セット
					lRslt = SendMessage( hHokyWnd, HKM_GETHOTKEY, 0, 0 );
					stAcce.key   = LOBYTE( lRslt );
					if( BST_CHECKED == IsDlgButtonChecked( hDlg, IDCB_FUNCKEY_SPACE ) )
					{	stAcce.key = VK_SPACE;	}
					stAcce.fVirt  = AccelHotModExchange( HIBYTE( lRslt ), 0 );
					stAcce.cmd    = 0;
					if( SUCCEEDED( AccelKeyBindExistCheck( hDlg, &stAcce, &cltAccel ) ) )
					{
						//	かぶってなかったら登録する
						iItem = WndTagGet( hHokyWnd );
						AccelKeyBindListMod( hDlg, iItem, &stAcce, &cltAccel );
					}
					return (INT_PTR)TRUE;


				case IDB_FUNCKEY_INIT:	//	設定を初期化する
					if( IDOK == MessageBox( hDlg, TEXT("단축키 설정을 초기값으로 되돌립니다."), TEXT("설정 리셋"), MB_OKCANCEL | MB_ICONQUESTION ) )
					{
						AccelKeySettingReset( hDlg, &cltAccel );
						AccelKeyListInit( hDlg, &cltAccel );
					}
					return (INT_PTR)TRUE;


				case IDB_FUNCKEY_FILEOUT:	//	設定をファイルに出力
					AccelKeyListOutput( hDlg );
					return (INT_PTR)TRUE;


				default:	break;
			}
			break;

		case WM_NOTIFY:
			return AccelKeyNotify( hDlg, (INT)(wParam), (LPNMHDR)(lParam), &cltAccel );

		default:	break;
	}

	return (INT_PTR)FALSE;
}
//-------------------------------------------------------------------------------------------------

/*!
	アクセルキー編集のノーティファイメッセージ処理
	@param[in]	hDlg		ダイヤログハンドル
	@param[in]	idFrom		発生したコモンのID番号
	@param[in]	pstNmhdr	イベント内容
	@param[in]	*pltAccel	アクセラキーテーブル
	@retval 0	メッセージは処理していない
	@retval no0	なんか処理された
*/
INT_PTR AccelKeyNotify( HWND hDlg, INT idFrom, LPNMHDR pstNmhdr, list<ACCEL> *pltAccel )
{
	LPNMLISTVIEW	pstLv;
	LVITEM			stLvi;
	BYTE	bMod;
	HWND	hHokyWnd;

	list<ACCEL>::iterator	itAccel;

	if( IDLV_FUNCKEY_LIST == idFrom )	//	一覧リストビューで
	{
		if( NM_CLICK == pstNmhdr->code )	//	クリッケされたら
		{
			pstLv = (LPNMLISTVIEW)pstNmhdr;
			pstLv->iItem;	//	そのアイテムを確認して

			ZeroMemory( &stLvi, sizeof(stLvi) );
			stLvi.mask     = LVIF_PARAM;	//	コマンドコードを確保する
			stLvi.iItem    = pstLv->iItem;
			ListView_GetItem( pstNmhdr->hwndFrom, &stLvi );

			hHokyWnd = GetDlgItem( hDlg, IDHKC_FUNCKEY_INPUT );
			WndTagSet( hHokyWnd , stLvi.iItem );	//	選択した行を確保

			for( itAccel = (*pltAccel).begin(); itAccel != (*pltAccel).end(); itAccel++ )
			{
				if( stLvi.lParam == itAccel->cmd )
				{
					bMod = AccelHotModExchange( itAccel->fVirt, 1 );
					if( 0x20 == itAccel->key )
					{	SendMessage( hHokyWnd , HKM_SETHOTKEY, MAKEWORD(itAccel->key, bMod), 0 );	}
					else{	SendMessage( hHokyWnd, HKM_SETHOTKEY, MAKEWORD(itAccel->key, (bMod|HOTKEYF_EXT)), 0 );	}

					break;			//		常にHOTKEYF_EXTいれると、Spaceが本当に空白になる
				}
			}
			if( itAccel == (*pltAccel).end() )	SendMessage( hHokyWnd, HKM_SETHOTKEY, 0, 0 );

			SetFocus( GetDlgItem( hDlg, IDHKC_FUNCKEY_INPUT ) );
		}
		return (INT_PTR)TRUE;
	}

	return (INT_PTR)FALSE;
}
//-------------------------------------------------------------------------------------------------

/*!
	アクセラテーブルを初期ファイルから確保する・メモリ確保するので返り値の扱いに注意
	@param[out]	piEntry	確保したエントリ数を戻す
	@return		確保したテーブル構造体のポインター・freeに注意
*/
LPACCEL AccelKeyTableLoadAlloc( LPINT piEntry )
{
	UINT	dCount, dValue;
	UINT	i, aim = 0;
	TCHAR	atKeyName[MIN_STRING];
	LPACCEL	pstAccel = NULL;

	//	初期状態
	dCount = GetPrivateProfileInt( TEXT("Accelerator"), TEXT("Count"), 0, gatCntxIni );
	if( 1 <= dCount )	//	データ有り
	{
		pstAccel = (LPACCEL)malloc( dCount * sizeof(ACCEL) );

		for( i = 0; dCount > i; i++ )
		{
			StringCchPrintf( atKeyName, MIN_STRING, TEXT("AcCMD%d"), i );
			dValue = GetPrivateProfileInt( TEXT("Accelerator"), atKeyName, 0, gatCntxIni );
			if( 0 == dValue )	continue;	//	設定が０なら何もしない
			pstAccel[aim].cmd = dValue;

			StringCchPrintf( atKeyName, MIN_STRING, TEXT("AcVirt%d"), i );
			dValue = GetPrivateProfileInt( TEXT("Accelerator"), atKeyName, 0, gatCntxIni );
			pstAccel[aim].fVirt = dValue;

			StringCchPrintf( atKeyName, MIN_STRING, TEXT("AcKey%d"), i );
			dValue = GetPrivateProfileInt( TEXT("Accelerator"), atKeyName, 0, gatCntxIni );
			pstAccel[aim].key = dValue;

			aim++;
		}
	}

	if( piEntry )	*piEntry = aim;

	return pstAccel;
}
//-------------------------------------------------------------------------------------------------

/*!
	キーバインドを参照して、文字列を作る
	@param[in]	pstAccel	アクセラキーテーブル
	@param[in]	ptBuffer	文字列入れるバッファのポインター
	@param[in]	cchSize		バッファの文字数
	@return		HRESULT		終了状態コード
*/
HRESULT AccelKeyBindString( LPACCEL pstAccel, LPTSTR ptBuffer, UINT_PTR cchSize )
{
	TCHAR	atKey[MIN_STRING];

	ZeroMemory( ptBuffer, cchSize * sizeof(TCHAR) );

//	FVIRTKEY  FNOINVERT  は常に含める

	if( FCONTROL & pstAccel->fVirt )	StringCchCat( ptBuffer, cchSize, TEXT("Ctrl + ") );
	if( FSHIFT   & pstAccel->fVirt )	StringCchCat( ptBuffer, cchSize, TEXT("Shift + ") );
	if( FALT     & pstAccel->fVirt )	StringCchCat( ptBuffer, cchSize, TEXT("Alt + ") );

	if( '0' <= pstAccel->key && pstAccel->key <= '9' )	//	VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
	{
		StringCchPrintf( atKey, MIN_STRING, TEXT("%c"), pstAccel->key );
	}
	else if( 'A' <= pstAccel->key && pstAccel->key <= 'Z' )	//	VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
	{
		StringCchPrintf( atKey, MIN_STRING, TEXT("%c"), pstAccel->key );
	}
	else if( 0x60 <= pstAccel->key && pstAccel->key <= 0x69 )	//	NUMPAD0 - NUMPAD9
	{
		StringCchPrintf( atKey, MIN_STRING, TEXT("NUMPAD%u"), pstAccel->key - 0x60 );
	}
	else if( 0x70 <= pstAccel->key && pstAccel->key <= 0x87 )	//	F1 - F24
	{
		StringCchPrintf( atKey, MIN_STRING, TEXT("F%u"), pstAccel->key - 0x70 + 1 );
	}
	else
	{
		switch( pstAccel->key )
		{
			case VK_CANCEL:		StringCchCopy( atKey, MIN_STRING, TEXT("Break") );	break;
			case VK_BACK:		StringCchCopy( atKey, MIN_STRING, TEXT("BackSpace") );	break;
			case VK_TAB:		StringCchCopy( atKey, MIN_STRING, TEXT("TAB") );	break;
			case VK_CLEAR:		StringCchCopy( atKey, MIN_STRING, TEXT("CLEAR") );	break;
			case VK_RETURN:		StringCchCopy( atKey, MIN_STRING, TEXT("Enter") );	break;
			case VK_PAUSE:		StringCchCopy( atKey, MIN_STRING, TEXT("Pause") );	break;
			case VK_CAPITAL:	StringCchCopy( atKey, MIN_STRING, TEXT("CAPITAL") );	break;
			case VK_KANA:		StringCchCopy( atKey, MIN_STRING, TEXT("KANA") );	break;
			case VK_ESCAPE:		StringCchCopy( atKey, MIN_STRING, TEXT("Esc") );	break;
			case VK_CONVERT:	StringCchCopy( atKey, MIN_STRING, TEXT("変換") );	break;
			case VK_NONCONVERT:	StringCchCopy( atKey, MIN_STRING, TEXT("无変換") );	break;
			case VK_SPACE:		StringCchCopy( atKey, MIN_STRING, TEXT("Space") );	break;
			case VK_PRIOR:		StringCchCopy( atKey, MIN_STRING, TEXT("PageUp") );	break;
			case VK_NEXT:		StringCchCopy( atKey, MIN_STRING, TEXT("PageDown") );	break;
			case VK_END:		StringCchCopy( atKey, MIN_STRING, TEXT("End") );	break;
			case VK_HOME:		StringCchCopy( atKey, MIN_STRING, TEXT("Home") );	break;
			case VK_LEFT:		StringCchCopy( atKey, MIN_STRING, TEXT("←") );	break;
			case VK_UP:			StringCchCopy( atKey, MIN_STRING, TEXT("↑") );	break;
			case VK_RIGHT:		StringCchCopy( atKey, MIN_STRING, TEXT("→") );	break;
			case VK_DOWN:		StringCchCopy( atKey, MIN_STRING, TEXT("↓") );	break;
			case VK_SELECT:		StringCchCopy( atKey, MIN_STRING, TEXT("SELECT") );	break;
			case VK_PRINT:		StringCchCopy( atKey, MIN_STRING, TEXT("PRINT") );	break;
			case VK_EXECUTE:	StringCchCopy( atKey, MIN_STRING, TEXT("EXECUTE") );	break;
			case VK_SNAPSHOT:	StringCchCopy( atKey, MIN_STRING, TEXT("PrintScr") );	break;
			case VK_INSERT:		StringCchCopy( atKey, MIN_STRING, TEXT("Insert") );	break;
			case VK_DELETE:		StringCchCopy( atKey, MIN_STRING, TEXT("Delete") );	break;
			case VK_HELP:		StringCchCopy( atKey, MIN_STRING, TEXT("Help") );	break;
			case VK_LWIN:		StringCchCopy( atKey, MIN_STRING, TEXT("左Win") );	break;
			case VK_RWIN:		StringCchCopy( atKey, MIN_STRING, TEXT("右Win") );	break;
			case VK_APPS:		StringCchCopy( atKey, MIN_STRING, TEXT("APPZ") );	break;
			case VK_SLEEP:		StringCchCopy( atKey, MIN_STRING, TEXT("SLEEP") );	break;
			case VK_MULTIPLY:	StringCchCopy( atKey, MIN_STRING, TEXT("NUM *") );	break;
			case VK_ADD:		StringCchCopy( atKey, MIN_STRING, TEXT("NUM +") );	break;
			case VK_SEPARATOR:	StringCchCopy( atKey, MIN_STRING, TEXT("NUM ,") );	break;
			case VK_SUBTRACT:	StringCchCopy( atKey, MIN_STRING, TEXT("NUM -") );	break;
			case VK_DECIMAL:	StringCchCopy( atKey, MIN_STRING, TEXT("NUM .") );	break;
			case VK_DIVIDE:		StringCchCopy( atKey, MIN_STRING, TEXT("NUM /") );	break;
			case VK_NUMLOCK:	StringCchCopy( atKey, MIN_STRING, TEXT("NumLock") );	break;
			case VK_SCROLL:		StringCchCopy( atKey, MIN_STRING, TEXT("ScrollLock") );	break;
			case VK_OEM_NEC_EQUAL:	StringCchCopy( atKey, MIN_STRING, TEXT("NUM =") );	break;
			case VK_BROWSER_BACK:		StringCchCopy( atKey, MIN_STRING, TEXT("戻る") );	break;
			case VK_BROWSER_FORWARD:	StringCchCopy( atKey, MIN_STRING, TEXT("進む") );	break;
			case VK_BROWSER_REFRESH:	StringCchCopy( atKey, MIN_STRING, TEXT("更新") );	break;
			case VK_BROWSER_STOP:		StringCchCopy( atKey, MIN_STRING, TEXT("停止") );	break;
			case VK_BROWSER_SEARCH:		StringCchCopy( atKey, MIN_STRING, TEXT("検索") );	break;
			case VK_BROWSER_FAVORITES:	StringCchCopy( atKey, MIN_STRING, TEXT("気入") );	break;
			case VK_BROWSER_HOME:		StringCchCopy( atKey, MIN_STRING, TEXT("ホム") );	break;
			case VK_VOLUME_MUTE:		StringCchCopy( atKey, MIN_STRING, TEXT("消音") );	break;
			case VK_VOLUME_DOWN:		StringCchCopy( atKey, MIN_STRING, TEXT("音下") );	break;
			case VK_VOLUME_UP:			StringCchCopy( atKey, MIN_STRING, TEXT("音上") );	break;
			case VK_MEDIA_NEXT_TRACK:	StringCchCopy( atKey, MIN_STRING, TEXT("次項") );	break;
			case VK_MEDIA_PREV_TRACK:	StringCchCopy( atKey, MIN_STRING, TEXT("前項") );	break;
			case VK_MEDIA_STOP:			StringCchCopy( atKey, MIN_STRING, TEXT("停止") );	break;
			case VK_MEDIA_PLAY_PAUSE:	StringCchCopy( atKey, MIN_STRING, TEXT("再生") );	break;
			case VK_LAUNCH_MAIL:		StringCchCopy( atKey, MIN_STRING, TEXT("メル") );	break;
			case VK_LAUNCH_MEDIA_SELECT:StringCchCopy( atKey, MIN_STRING, TEXT("選択") );	break;
			case VK_LAUNCH_APP1:		StringCchCopy( atKey, MIN_STRING, TEXT("APP1") );	break;
			case VK_LAUNCH_APP2:		StringCchCopy( atKey, MIN_STRING, TEXT("APP2") );	break;
			case VK_OEM_1:		StringCchCopy( atKey, MIN_STRING, TEXT(":") );	break;
			case VK_OEM_PLUS:	StringCchCopy( atKey, MIN_STRING, TEXT(";") );	break;
			case VK_OEM_COMMA:	StringCchCopy( atKey, MIN_STRING, TEXT(",") );	break;
			case VK_OEM_MINUS:	StringCchCopy( atKey, MIN_STRING, TEXT("-") );	break;
			case VK_OEM_PERIOD:	StringCchCopy( atKey, MIN_STRING, TEXT(".") );	break;
			case VK_OEM_2:		StringCchCopy( atKey, MIN_STRING, TEXT("/") );	break;
			case VK_OEM_3:		StringCchCopy( atKey, MIN_STRING, TEXT("@") );	break;
			case VK_OEM_4:		StringCchCopy( atKey, MIN_STRING, TEXT("[") );	break;
			case VK_OEM_5:		StringCchCopy( atKey, MIN_STRING, TEXT("\\") );	break;	//	￥
			case VK_OEM_6:		StringCchCopy( atKey, MIN_STRING, TEXT("]") );	break;
			case VK_OEM_7:		StringCchCopy( atKey, MIN_STRING, TEXT("^") );	break;
			case VK_OEM_8:		StringCchCopy( atKey, MIN_STRING, TEXT("_") );	break;
			case VK_OEM_102:	StringCchCopy( atKey, MIN_STRING, TEXT("ろ") );	break;	//	ろ
			case VK_OEM_ATTN:	StringCchCopy( atKey, MIN_STRING, TEXT("CapsLock") );	break;
			case VK_OEM_COPY:	StringCchCopy( atKey, MIN_STRING, TEXT("カ夕ひら") );	break;
			case VK_OEM_AUTO:	StringCchCopy( atKey, MIN_STRING, TEXT("半/全 漢1") );	break;
			case VK_OEM_ENLW:	StringCchCopy( atKey, MIN_STRING, TEXT("半/全 漢2") );	break;

			//	足りない分はＳＤＫから追加する
			default:	StringCchPrintf( atKey, MIN_STRING, TEXT("0x%02X"), pstAccel->key );	break;
		}
	}
//0x40 : unassigned
//0x07 : unassigned
//0x0A - 0x0B : reserved
//0x5E : reserved
//0x88 - 0x8F : unassigned
//0x97 - 0x9F : unassigned
//0xB8 - 0xB9 : reserved
//0xC1 - 0xD7 : reserved
//0xD8 - 0xDA : unassigned
//0xE0 : reserved
//0xE8 : unassigned
//0xFF : reserved

	StringCchCat( ptBuffer, cchSize, atKey );

	return S_OK;
}
//-------------------------------------------------------------------------------------------------

/*!
	コマンド番号を参照して、ヒットしたらアクセル文字列を作ってくっつける
	@param[in]	ptText		処理結果をくっつける文字列ポインター
	@param[in]	cchSize		バッファの文字数
	@param[in]	dCommand	コマンド番号
	@param[in]	pstAccel	アクセラキーテーブル
	@param[in]	iEntry		テーブルのデータ数
	@return		HRESULT		終了状態コード
*/
HRESULT AccelKeyTextBuild( LPTSTR ptText, UINT_PTR cchSize, DWORD dCommand, CONST LPACCEL pstAccel, INT iEntry )
{
	TCHAR	atKeystr[SUB_STRING];
	INT		i;

	for( i = 0; iEntry > i; i++ )
	{
		if( pstAccel[i].cmd == dCommand )
		{
			AccelKeyBindString( &(pstAccel[i]), atKeystr, SUB_STRING );

			StringCchCat( ptText, cchSize, TEXT("\r\n") );
			StringCchCat( ptText, cchSize, atKeystr );

			return S_OK;
		}
	}

	return E_OUTOFMEMORY;
}
//-------------------------------------------------------------------------------------------------

/*!
	アクセルキー編集のリストビュー初期化
	@param[in]	hDlg		ダイヤログハンドル
	@param[in]	*pltAccel	アクセラキーテーブル
*/
VOID AccelKeyListInit( HWND hDlg, list<ACCEL> *pltAccel )
{
	HWND		hLvWnd;
	LVCOLUMN	stLvColm;
	LVITEM		stItem;
	RECT		rect;
	LONG		width, i, j;
	TCHAR		atBuffer[SUB_STRING];

	list<ACCEL>::iterator	itAccel;

	hLvWnd = GetDlgItem( hDlg, IDLV_FUNCKEY_LIST );
	GetClientRect( hLvWnd, &rect );
	width = rect.right - 23;
	width /= 2;

	ZeroMemory( &stLvColm, sizeof(LVCOLUMN) );
	stLvColm.mask     = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	stLvColm.fmt      = LVCFMT_LEFT;

	stLvColm.iSubItem = 0;
	stLvColm.pszText  = TEXT("기능");
	stLvColm.cx       = width;
	ListView_InsertColumn( hLvWnd, 0, &stLvColm );

	stLvColm.iSubItem = 1;
	stLvColm.pszText  = TEXT("설정된 단축키");
	stLvColm.cx       = width;
	ListView_InsertColumn( hLvWnd, 1, &stLvColm );


	ZeroMemory( &stItem, sizeof(LVITEM) );

	for( i = 0, j = 0; ALL_ITEMS > i; i++ )
	{
		stItem.iItem = j;

		//	関係無いやつは飛ばす
		if( 0 == gstContextItem[i].dCommandoID || 
		IDM_MN_UNISPACE     == gstContextItem[i].dCommandoID || 
		IDM_MN_COLOUR_SEL   == gstContextItem[i].dCommandoID || 
		IDM_MN_INSFRAME_SEL == gstContextItem[i].dCommandoID || 
		IDM_MN_USER_REFS    == gstContextItem[i].dCommandoID )
		{	continue;	}

		StringCchCopy( atBuffer, SUB_STRING, gstContextItem[i].atString );
		stItem.mask     = LVIF_TEXT | LVIF_PARAM;
		stItem.pszText  = atBuffer;
		stItem.lParam   = gstContextItem[i].dCommandoID;
		stItem.iSubItem = 0;
		ListView_InsertItem( hLvWnd, &stItem );

		ZeroMemory( atBuffer, sizeof(atBuffer) );

		for( itAccel = (*pltAccel).begin(); itAccel != (*pltAccel).end(); itAccel++ )
		{
			if( gstContextItem[i].dCommandoID == itAccel->cmd )
			{
				AccelKeyBindString( &(*itAccel), atBuffer, SUB_STRING );
				break;
			}
		}

		stItem.mask     = LVIF_TEXT;
		stItem.pszText  = atBuffer;
		stItem.iSubItem = 1;
		ListView_SetItem( hLvWnd, &stItem );

		j++;
	}

	return;
}
//-------------------------------------------------------------------------------------------------

/*!
	アクセルキーとホットキーの修飾子を入替
	@param[in]	bSrc	元の修飾子コード
	@param[in]	bDrct	非０アクセル→ホット　０ホット→アクセル
	@return	変換したコード
*/
BYTE AccelHotModExchange( BYTE bSrc, BOOLEAN bDrct )
{
	BYTE	bDest = 0;

	if( bDrct )	//	アクセル→ホット
	{
		if( bSrc & FSHIFT )		bDest |= HOTKEYF_SHIFT;		//	シフト
		if( bSrc & FCONTROL )	bDest |= HOTKEYF_CONTROL;	//	コントロール
		if( bSrc & FALT )		bDest |= HOTKEYF_ALT;		//	アルタネート
	}
	else	//	ホット→アクセル
	{
		if( bSrc & HOTKEYF_SHIFT )		bDest |= FSHIFT;	//	シフト
		if( bSrc & HOTKEYF_CONTROL )	bDest |= FCONTROL;	//	コントロール
		if( bSrc & HOTKEYF_ALT )		bDest |= FALT;		//	アルタネート

		bDest |= (FVIRTKEY|FNOINVERT);	//	常にある
	}

	return bDest;
}
//-------------------------------------------------------------------------------------------------

/*!
	アクセルテーブルを保存
	@param[in]	*pltAccel	アクセラキーテーブル
	@return		HRESULT		終了状態コード
*/
HRESULT AccelKeyTableSave( list<ACCEL> *pltAccel )
{
	INT_PTR	i;
	TCHAR	atKeyName[MIN_STRING], atBuff[MIN_STRING];
	list<ACCEL>::iterator	itAccel;

	//	一旦セクションを空にする
	ZeroMemory( atBuff, sizeof(atBuff) );
	WritePrivateProfileSection( TEXT("Accelerator"), atBuff, gatCntxIni );

	i = 0;
	for( itAccel = (*pltAccel).begin(); itAccel != (*pltAccel).end(); itAccel++ )
	{
		StringCchPrintf( atKeyName, MIN_STRING, TEXT("AcCMD%d"), i );
		StringCchPrintf( atBuff, MIN_STRING, TEXT("%u"), itAccel->cmd );
		WritePrivateProfileString( TEXT("Accelerator"), atKeyName, atBuff, gatCntxIni );

		StringCchPrintf( atKeyName, MIN_STRING, TEXT("AcVirt%d"), i );
		StringCchPrintf( atBuff, MIN_STRING, TEXT("%u"), itAccel->fVirt );
		WritePrivateProfileString( TEXT("Accelerator"), atKeyName, atBuff, gatCntxIni );

		StringCchPrintf( atKeyName, MIN_STRING, TEXT("AcKey%d"), i );
		StringCchPrintf( atBuff, MIN_STRING, TEXT("%u"), itAccel->key );
		WritePrivateProfileString( TEXT("Accelerator"), atKeyName, atBuff, gatCntxIni );

		i++;
	}

	StringCchPrintf( atBuff, MIN_STRING, TEXT("%u"), i );
	WritePrivateProfileString( TEXT("Accelerator"), TEXT("Count"), atBuff, gatCntxIni );

	return S_OK;
}
//-------------------------------------------------------------------------------------------------

/*!
	アクセル設定を初期状態にアッー
	@param[in]	hDlg		ダイヤログハンドル
	@param[in]	*pltAccel	アクセラキーテーブル
	@return		HRESULT		終了状態コード
*/
HRESULT AccelKeySettingReset( HWND hDlg, list<ACCEL> *pltAccel )
{
	HWND	hLvWnd;
	HACCEL	hAccel;	//	
	LPACCEL	pstAccel = NULL;
	INT		iItems, i;

	//	元々のテーブルを確保
	hAccel = LoadAccelerators( ghInst, MAKEINTRESOURCE(IDC_ORINRINEDITOR) );

	//	まず個数確保
	iItems = CopyAcceleratorTable( hAccel, NULL, 0 );
	if( 0 >= iItems )	return E_POINTER;

	pstAccel = (LPACCEL)malloc( iItems * sizeof(ACCEL) );
	if( !(pstAccel) )	return NULL;

	//	本体確保
	iItems = CopyAcceleratorTable( hAccel, pstAccel, iItems );

	DestroyAcceleratorTable( hAccel );	//	全部汚倭ったらぶっ壊しておく

	(*pltAccel).clear();	//	クルヤー

	for( i = 0; iItems > i; i++ ){	(*pltAccel).push_back( pstAccel[i] );	}

	FREE( pstAccel );

	hLvWnd = GetDlgItem( hDlg, IDLV_FUNCKEY_LIST );
	ListView_DeleteAllItems( hLvWnd );	//	リストビューは壊しておく方が早い

	return S_OK;
}
//-------------------------------------------------------------------------------------------------

/*!
	設定をファイルにエクスポートする
	@param[in]	hDlg	ダイヤログハンドル
	@return		HRESULT	終了状態コード
*/
HRESULT AccelKeyListOutput( HWND hDlg )
{
//	CONST  WCHAR	rtHead = 0xFEFF;	//	ユニコードテキストヘッダ
	//	ファイル形式は？　SJISかUTF8でいい

	HANDLE	hFile;
	DWORD	wrote;
	BOOLEAN	bOpened;

	OPENFILENAME	stSaveFile;

	INT		i, iAccEntry;
	INT		j;
	LPACCEL	pstAccel;

	UINT_PTR	cchSz;
	INT		cbSize;


	TCHAR	atFilePath[MAX_PATH], atFileName[MAX_STRING];
	TCHAR	atCmdName[MIN_STRING], atKeyBind[SUB_STRING];
	TCHAR	atBuffer[MAX_PATH];

	CHAR	acString[BIG_STRING];


	ZeroMemory( &stSaveFile, sizeof(OPENFILENAME) );

	ZeroMemory( atFilePath,  sizeof(atFilePath) );
	ZeroMemory( atFileName,  sizeof(atFileName) );
	ZeroMemory( atBuffer,  sizeof(atBuffer) );

	StringCchCopy( atFilePath, MAX_PATH, TEXT("Accelerator.txt") );
#if 1
	//ここで FileSaveDialogue を出す
	stSaveFile.lStructSize     = sizeof(OPENFILENAME);
	stSaveFile.hwndOwner       = hDlg;
	stSaveFile.lpstrFilter     = TEXT("텍스트 파일 ( *.txt )\0*.txt\0모든 파일 ( *.* )\0*.*\0\0");
	stSaveFile.nFilterIndex    = 1;	//	デフォのフィルタ選択肢
	stSaveFile.lpstrFile       = atFilePath;
	stSaveFile.nMaxFile        = MAX_PATH;
	stSaveFile.lpstrFileTitle  = atFileName;
	stSaveFile.nMaxFileTitle   = MAX_STRING;
	stSaveFile.lpstrDefExt     = TEXT("txt");
//	stSaveFile.lpstrInitialDir = 
	stSaveFile.lpstrTitle      = TEXT("어떤 이름으로 저장할까요?");
	stSaveFile.Flags           = OFN_EXPLORER | OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY;

	bOpened = GetSaveFileName( &stSaveFile );
	if( !(bOpened) ){	return  E_ABORT;	}
	//	キャンセルしてたら何もしない
#endif
	hFile = CreateFile( atFilePath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
	if( INVALID_HANDLE_VALUE == hFile )
	{
		MessageBox( hDlg, TEXT("단축키 설정을 내보내지 못했습니다."), NULL, MB_OK | MB_ICONERROR );
		return E_HANDLE;
	}
	SetFilePointer( hFile, 0, NULL, FILE_BEGIN );

	//WriteFile( hFile, &rtHead, 2, &wrote, NULL );

	//	設定されてるテーブルを確保
	pstAccel = AccelKeyTableGetAlloc( &iAccEntry );
	for( i = 0; iAccEntry > i; i++ )
	{
		AccelKeyBindString( &(pstAccel[i]), atKeyBind, SUB_STRING );

		StringCchCopy( atCmdName, MIN_STRING, TEXT("（이름 불명）") );
		for( j = 0; FULL_ITEMS > j; j++ )
		{
			if( gstContextItem[j].dCommandoID == pstAccel[i].cmd )
			{
				StringCchCopy( atCmdName, MIN_STRING, gstContextItem[j].atString );
				break;
			}
		}

		StringCchPrintf( atBuffer, MAX_PATH, TEXT("%s\t%s\r\n"), atCmdName, atKeyBind );
		StringCchLength( atBuffer, MAX_PATH, &cchSz );

		cbSize = WideCharToMultiByte( CP_ACP, WC_NO_BEST_FIT_CHARS, atBuffer, -1, acString, BIG_STRING, NULL, NULL );
									//	CP_UTF8, 0	
		//	変換文字数にはヌルターミネータが含まれているので注意
		WriteFile( hFile, acString, cbSize-1, &wrote, NULL );
	}
	FREE( pstAccel );

	SetEndOfFile( hFile );
	CloseHandle( hFile );

	MessageBox( hDlg, TEXT("단축키 설정을 내보냈습니다."), TEXT("（・∀・）ｂ"), MB_OK | MB_ICONINFORMATION );

	return S_OK;
}
//-------------------------------------------------------------------------------------------------

/*!
	指定のコマンドが使われてるかどうか確認
	@param[in]	hDlg		ダイヤログハンドル
	@param[in]	pstAccel	アクセラキーテーブル
	@param[in]	*pltAccel	既存のやつの一覧
	@return		HRESULT		終了状態コード　S_OKかぶり無し　E_ACCESSDENIEDかぶり有った
*/
HRESULT AccelKeyBindExistCheck( HWND hDlg, LPACCEL pstAccel, list<ACCEL> *pltAccel )
{
	INT	i;
	//BYTE	fVirt;
	WORD	dCommand;
	list<ACCEL>::iterator	itAccel;
	TCHAR	atFuncName[MIN_STRING], atMsg[MAX_STRING];

	for( itAccel = (*pltAccel).begin(); itAccel != (*pltAccel).end(); itAccel++ )
	{
		//	同じのがあるかどうか探す
		//fVirt= itAccel->fVirt;
		//fVirt &= ~(FVIRTKEY|FNOINVERT);変換時に付け足してるので要らない
		if( pstAccel->key == itAccel->key && pstAccel->fVirt == itAccel->fVirt )
		{
			//	同じのがあった
			dCommand = itAccel->cmd;
			StringCchCopy( atFuncName, MIN_STRING, TEXT("（이름 불명）") );

			for( i = 0; FULL_ITEMS > i; i++ )
			{
				if( dCommand == gstContextItem[i].dCommandoID )
				{
					StringCchCopy( atFuncName, MIN_STRING, gstContextItem[i].atString );
					break;
				}
			}

			StringCchPrintf( atMsg, MAX_STRING, TEXT("이 단축키는「%s」로 지정되어 있습니다."), atFuncName );
			MessageBox( hDlg, atMsg, TEXT("중복 단축키 안내"), MB_OK | MB_ICONWARNING );

			return E_ACCESSDENIED;
		}
	}
	
	return S_OK;
}
//-------------------------------------------------------------------------------------------------

/*!
	アクセルキー編集のリストビューにデータ書込
	@param[in]	hDlg		ダイヤログハンドル
	@param[in]	iItem		操作する行番号
	@param[in]	pstAccel	アクセラキーテーブル
	@param[in]	*pltAccel	既存のやつの一覧
	@return		HRESULT		終了状態コード
*/
HRESULT AccelKeyBindListMod( HWND hDlg, INT iItem, LPACCEL pstAccel, list<ACCEL> *pltAccel )
{
	HWND	hLvWnd = GetDlgItem( hDlg, IDLV_FUNCKEY_LIST );
	HWND	hHkcWnd = GetDlgItem( hDlg, IDHKC_FUNCKEY_INPUT );
	LVITEM	stLvi;
	TCHAR	atBuffer[SUB_STRING];
	WORD	dCommand;
	list<ACCEL>::iterator	itAccel;

	//	該当行から、コマンド番号を持ってくる
	ZeroMemory( &stLvi, sizeof(stLvi) );
	stLvi.mask     = LVIF_PARAM;	//	コマンドコードを確保する
	stLvi.iItem    = iItem;
	ListView_GetItem( hLvWnd, &stLvi );
	dCommand = stLvi.lParam;

	for( itAccel = (*pltAccel).begin(); itAccel != (*pltAccel).end(); itAccel++ )
	{
		if( dCommand ==  itAccel->cmd ){	break;	}
		//	ヒットしたらソレでおｋ
	}

	if( pstAccel )	//	変更・追加
	{
		if( itAccel == (*pltAccel).end() )	//	追加
		{
			pstAccel->cmd = dCommand;
			(*pltAccel).push_back( *pstAccel );
		}
		else	//	変更
		{
			itAccel->key   = pstAccel->key;
			itAccel->fVirt = pstAccel->fVirt;
		}
		
		//	表示用文字列作って
		AccelKeyBindString( pstAccel, atBuffer, SUB_STRING );
		ZeroMemory( &stLvi, sizeof(stLvi) );
		stLvi.mask     = LVIF_TEXT;	//	コマンドコードを確保する
		stLvi.iItem    = iItem;
		stLvi.iSubItem = 1;
		stLvi.pszText  = atBuffer;
		ListView_SetItem( hLvWnd, &stLvi );
	}
	else	//	解除
	{
		//	ヒットしてないなんてことは無いはずだが
		if( itAccel == (*pltAccel).end( ) ){	return E_HANDLE;	}

		//	該当要素を削除
		(*pltAccel).erase( itAccel );
		//	ホットキーコントロールを空に
		SendMessage( hHkcWnd, HKM_SETHOTKEY, 0, 0 );
		//	リストビューの表示も空にする
		ZeroMemory( atBuffer, sizeof(atBuffer) );
		ZeroMemory( &stLvi, sizeof(stLvi) );
		stLvi.mask     = LVIF_TEXT;	//	コマンドコードを確保する
		stLvi.iItem    = iItem;
		stLvi.iSubItem = 1;
		stLvi.pszText  = atBuffer;
		ListView_SetItem( hLvWnd, &stLvi );
	}

	return S_OK;
}
//-------------------------------------------------------------------------------------------------

/*!
	メニュー文字列に、アクセラーキー名称を割り当てていく
	@param[in]	hWnd		メニューのあるウインドウハンドル
	@param[in]	pstAccel	内容テーブル・無い時はNULL
	@param[in]	iEntry		テーブルのエントリ数
	@return		HRESULT		終了状態コード
*/
HRESULT AccelKeyMenuRewrite( HWND hWnd, LPACCEL pstAccel, CONST INT iEntry )
{
	HMENU		hMenu;
	WORD		dCmd;
	INT			i, j, iRslt;
	UINT		mRslt;
	UINT_PTR	d, cchSz;
	BOOLEAN		bModify;
	TCHAR		atBuffer[MAX_STRING], atBind[SUB_STRING];

	hMenu = GetMenu( hWnd );	//	サブメニューまで全部イケる

	for( i = 0; FULL_ITEMS > i; i++ )
	{
		//	関係無いやつは飛ばす
		if( 0 == gstContextItem[i].dCommandoID )	continue;

		dCmd = gstContextItem[i].dCommandoID;	//	基本的にこれでヒットするはず
		ZeroMemory( atBuffer, sizeof(atBuffer) );
		iRslt = GetMenuString( hMenu, dCmd, atBuffer, MAX_STRING, MF_BYCOMMAND );
		if( !(iRslt) )	continue;

		bModify = FALSE;

		//	先の内容を破壊する
		StringCchLength( atBuffer, MAX_STRING, &cchSz );
		for( d = 0; cchSz > d; d++ )
		{
			if( TEXT('\t') == atBuffer[d] )
			{
				atBuffer[d] = 0;
				bModify = TRUE;
				break;
			}
		}

		//	このコマンドのエントリーはあるか
		for( j = 0; iEntry > j; j++ )
		{
			if( dCmd == pstAccel[j].cmd )	//	あったら作成
			{
				ZeroMemory( atBind, sizeof(atBind) );
				AccelKeyBindString( &(pstAccel[j]), atBind, SUB_STRING );

				StringCchCat( atBuffer, MAX_STRING, TEXT("\t") );
				StringCchCat( atBuffer, MAX_STRING, atBind );

				bModify = TRUE;
				break;
			}
		}

		if( bModify )
		{
			//	必要に応じてチェック状態を確保する
			mRslt = GetMenuState( hMenu, dCmd, MF_BYCOMMAND );

			ModifyMenu( hMenu, dCmd, (MF_CHECKED & mRslt), dCmd, atBuffer );
			//	MF_BYCOMMAND | MF_STRING は両方０なので、必要なのはチェックの是非だけ
		}
	}

	DrawMenuBar( hWnd );

	return S_OK;
}
//-------------------------------------------------------------------------------------------------

#endif
