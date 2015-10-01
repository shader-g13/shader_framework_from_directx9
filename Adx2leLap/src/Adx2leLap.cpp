/// @file Adx2leLap.cpp
/// @brief Adx2leラップクラス
/// @date 2015/09/30
/// @author syuki nishida

#include "Adx2leLap.h"

/// @fn MyAlloc
/// @brief メモリ確保関数
/// @param[in] obj
/// @param[in] size サイズ
static void* myAlloc(void* obj, CriUint32 size) { return new void*[size]; }

/// @fn MyFree
/// @brief メモリ開放関数
/// @param[in] obj
/// @param[in] ptr 開放するポインタ
static void myFree(void* obj, void* ptr) { delete[] ptr; }

/// @fn MyError
/// @brief エラー関数
static void myError(const CriChar8* errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray) { OutputDebugString(criErr_ConvertIdToMessage(errid, p1, p2)); }

/// @fn Adx2leLap
/// @brief コンストラクタ
Adx2leLap::Adx2leLap() {
  // エラーコールバック関数の登録
  criErr_SetCallback(myError);

  // メモリアロケータの登録
  criAtomEx_SetUserAllocator(myAlloc, myFree, nullptr);

  // ライブラリ初期化
  criAtomEx_Initialize_PC(nullptr, nullptr, 0);

  // ストリーミング用バッファの作成
  _dbas = criAtomDbas_Create(nullptr, nullptr, 0);
}

/// @fn ~Adx2leLap
/// @brief デストラクタ
Adx2leLap::~Adx2leLap() {
  // ライブラリの終了
  criAtomEx_Finalize_PC();
}

/// @fn Start
/// @brief クラスを始める
/// @param[in] acf_file 全体ファイルパス
void Adx2leLap::Start(const char* acf_file) {
  // 全体設定ファイルの登録
  criAtomEx_RegisterAcfFile(nullptr, acf_file, nullptr, 0);

  // DSPバス設定の登録
  criAtomEx_AttachDspBusSetting("DspBusSetting_0", nullptr, 0);

  // ボイスプールの作成（ストリーム再生対応）
  CriAtomExStandardVoicePoolConfig vpconfig;
  criAtomExVoicePool_SetDefaultConfigForStandardVoicePool(&vpconfig);
  vpconfig.player_config.streaming_flag = CRI_TRUE;
  _voice_pool = criAtomExVoicePool_AllocateStandardVoicePool(&vpconfig, nullptr, 0);
}

/// @fn End
/// @brief プロジェクトを終える
void Adx2leLap::End() {
  // ボイスプールの解放
  criAtomExVoicePool_Free(_voice_pool);

  // 全体設定ファイルの登録解除
  criAtomEx_UnregisterAcf();
}

/// @fn LoadSoundFile
/// @brief サウンドファイル読み込み
/// @param[in] key サウンドデータ識別用文字列
/// @param[in] acb ACBファイルパス
/// @param[in] acw ACWファイルパス
void Adx2leLap::LoadSoundFile(const char* key, const char* acb, const char* awb) {
  CriAtomExAcbHn handle = criAtomExAcb_LoadAcbFile(
    nullptr, acb, nullptr, awb, nullptr, 0);
  _ASSERT_EXPR(_acb_handle_container.count(key) == 0,
    L"Adx2leLap : 既に登録されたキー");
  _acb_handle_container[key] = handle;
}

/// @fn UnloadSoundFile
/// @brief サウンドファイルけし
/// @param[in] key サウンドデータ識別文字列
void Adx2leLap::UnloadSoundFile(const char* key) {
  _ASSERT_EXPR(_acb_handle_container.count(key), L"Adx2leLap : 登録されてないキー");
  CriAtomExAcbHn handle = _acb_handle_container[key];
  _acb_handle_container.erase(key);
  criAtomExAcb_Release(handle);
}

//EOF