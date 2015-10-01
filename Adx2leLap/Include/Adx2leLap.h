/// @file Adx2leLap.cpp
/// @brief Adx2leラップクラス
/// @date 2015/09/30
/// @author syuki nishida
#pragma once

#include <cri_adx2le.h>
#include <string>
#include <map>

class Adx2leLap {
public:
  /// @fn Adx2leLap
  /// @brief コンストラクタ
  Adx2leLap();

  /// @fn ~Adx2leLap
  /// @brief デストラクタ
  virtual ~Adx2leLap();

  /// @fn Start
  /// @brief プロジェクトを始める
  /// @param[in] acf_file 全体ファイルパス
  void Start(const char* acf_file);

  /// @fn End
  /// @brief プロジェクトを終える
  void End();

  /// @fn LoadSoundFile
  /// @brief サウンドファイル読み込み
  /// @param[in] key サウンドデータ識別用文字列
  /// @param[in] acb ACBファイルパス
  /// @param[in] acw ACWファイルパス
  void LoadSoundFile(const char* key, const char* acb, const char* awb);

  /// @fn UnloadSoundFile
  /// @brief サウンドファイルけし
  /// @param[in] key サウンドデータ識別文字列
  void UnloadSoundFile(const char* key);

protected:

private:
  CriAtomDbasId _dbas;
  CriAtomExVoicePoolHn _voice_pool;

  std::map<std::string, CriAtomExAcbHn> _acb_handle_container;
};

//EOF