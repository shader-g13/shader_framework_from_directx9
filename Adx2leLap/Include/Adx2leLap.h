/// @file Adx2leLap.cpp
/// @brief Adx2le���b�v�N���X
/// @date 2015/09/30
/// @author syuki nishida
#pragma once

#include <cri_adx2le.h>
#include <string>
#include <map>

class Adx2leLap {
public:
  /// @fn Adx2leLap
  /// @brief �R���X�g���N�^
  Adx2leLap();

  /// @fn ~Adx2leLap
  /// @brief �f�X�g���N�^
  virtual ~Adx2leLap();

  /// @fn Start
  /// @brief �v���W�F�N�g���n�߂�
  /// @param[in] acf_file �S�̃t�@�C���p�X
  void Start(const char* acf_file);

  /// @fn End
  /// @brief �v���W�F�N�g���I����
  void End();

  /// @fn LoadSoundFile
  /// @brief �T�E���h�t�@�C���ǂݍ���
  /// @param[in] key �T�E���h�f�[�^���ʗp������
  /// @param[in] acb ACB�t�@�C���p�X
  /// @param[in] acw ACW�t�@�C���p�X
  void LoadSoundFile(const char* key, const char* acb, const char* awb);

  /// @fn UnloadSoundFile
  /// @brief �T�E���h�t�@�C������
  /// @param[in] key �T�E���h�f�[�^���ʕ�����
  void UnloadSoundFile(const char* key);

protected:

private:
  CriAtomDbasId _dbas;
  CriAtomExVoicePoolHn _voice_pool;

  std::map<std::string, CriAtomExAcbHn> _acb_handle_container;
};

//EOF