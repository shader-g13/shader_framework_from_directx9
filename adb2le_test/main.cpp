#include <stdio.h>

#include <cri_adx2le.h>
#pragma comment(lib, "cri_ware_pcx86_LE_import.lib")
#define ACF_FILE ("res/adx/Test.acf")
#define ACB_FILE ("res/adx/CueSheetTest.acb")

/// @brief エラーコールバック関数のユーザ実装
static void user_error_callback_func(const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray) {
  const CriChar8 *errmsg;
  /* エラーコードからエラー文字列に変換してコンソール出力する */
  errmsg = criErr_ConvertIdToMessage(errid, p1, p2);
  OutputDebugString(errmsg);
  return;
}

/// @brief メモリ確保関数のユーザ実装
void *user_alloc_func(void *obj, CriUint32 size) {
  void *ptr;
  ptr = malloc(size);
  return ptr;
}

/// @brief メモリ解放関数のユーザ実装
void user_free_func(void *obj, void *ptr) {
  free(ptr);
}

void main() {

  CriAtomExVoicePoolHn voice_pool;   // ボイスプールハンドル
  CriAtomDbasId dbas;                // D-BASハンドル

  // エラーコールバック関数の登録
  criErr_SetCallback(user_error_callback_func);

  // メモリアロケータの登録
  criAtomEx_SetUserAllocator(user_alloc_func, user_free_func, NULL);

  // ライブラリ初期化
  criAtomEx_Initialize_PC(NULL, NULL, 0);

  // ストリーミング用バッファの作成
  dbas = criAtomDbas_Create(NULL, NULL, 0);

  // 全体設定ファイルの登録
  criAtomEx_RegisterAcfFile(NULL, ACF_FILE, NULL, 0);

  // DSPバス設定の登録
  criAtomEx_AttachDspBusSetting("DspBusSetting_0", NULL, 0);

  // ボイスプールの作成（ストリーム再生対応）
  CriAtomExStandardVoicePoolConfig vpconfig;
  criAtomExVoicePool_SetDefaultConfigForStandardVoicePool(&vpconfig);
  vpconfig.player_config.streaming_flag = CRI_TRUE;
  voice_pool = criAtomExVoicePool_AllocateStandardVoicePool(&vpconfig, NULL, 0);
  // MEMO: ストリーム再生無しなら、ボイスプールは構造体NULL指定で可


  CriAtomExAcbHn acb_hn;             // ACBハンドル

  /* サウンドデータの読み込み */
  acb_hn = criAtomExAcb_LoadAcbFile(NULL, ACB_FILE, nullptr, NULL, NULL, 0);

  CriAtomExPlayerHn player;          // プレーヤハンドル
  // プレーヤハンドルの作成
  player = criAtomExPlayer_Create(NULL, NULL, 0);

  // キューの指定
  criAtomExPlayer_SetCueId(player, acb_hn, 0);
  // キューの再生開始
  criAtomExPlayer_Start(player);


  CriAtomExPlaybackId playback_id;

  // キュー再生とプレイバックIDの記録
  criAtomExPlayer_SetCueId(player, acb_hn, 0);
  playback_id = criAtomExPlayer_Start(player);

  auto msec = criAtomExPlayback_GetTime(playback_id);
  for (; msec < 10000;) {

    // 再生時刻の取得
    msec = criAtomExPlayback_GetTime(playback_id);

    // 再生終了の判定
    if (criAtomExPlayback_GetStatus(playback_id) == CRIATOMEXPLAYBACK_STATUS_REMOVED) {
      // 再生終了
    }



    printf("%dmsec\n", msec);

    /* ADX2サーバ処理の実行 */
    criAtomEx_ExecuteMain();
  }

  /* プレーヤハンドルの破棄 */
  criAtomExPlayer_Destroy(player);

  /* ACBハンドルの解放 */
  criAtomExAcb_Release(acb_hn);

  /* ボイスプールの解放 */
  criAtomExVoicePool_Free(voice_pool);

  /* 全体設定ファイルの登録解除 */
  criAtomEx_UnregisterAcf();

  /* ライブラリの終了 */
  criAtomEx_Finalize_PC();

}