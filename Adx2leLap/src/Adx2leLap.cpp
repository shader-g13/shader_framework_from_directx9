/// @file Adx2leLap.cpp
/// @brief Adx2le���b�v�N���X
/// @date 2015/09/30
/// @author syuki nishida

#include "Adx2leLap.h"

/// @fn MyAlloc
/// @brief �������m�ۊ֐�
/// @param[in] obj
/// @param[in] size �T�C�Y
static void* myAlloc(void* obj, CriUint32 size) { return new void*[size]; }

/// @fn MyFree
/// @brief �������J���֐�
/// @param[in] obj
/// @param[in] ptr �J������|�C���^
static void myFree(void* obj, void* ptr) { delete[] ptr; }

/// @fn MyError
/// @brief �G���[�֐�
static void myError(const CriChar8* errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray) { OutputDebugString(criErr_ConvertIdToMessage(errid, p1, p2)); }

/// @fn Adx2leLap
/// @brief �R���X�g���N�^
Adx2leLap::Adx2leLap() {
  // �G���[�R�[���o�b�N�֐��̓o�^
  criErr_SetCallback(myError);

  // �������A���P�[�^�̓o�^
  criAtomEx_SetUserAllocator(myAlloc, myFree, nullptr);

  // ���C�u����������
  criAtomEx_Initialize_PC(nullptr, nullptr, 0);

  // �X�g���[�~���O�p�o�b�t�@�̍쐬
  _dbas = criAtomDbas_Create(nullptr, nullptr, 0);
}

/// @fn ~Adx2leLap
/// @brief �f�X�g���N�^
Adx2leLap::~Adx2leLap() {
  // ���C�u�����̏I��
  criAtomEx_Finalize_PC();
}

/// @fn Start
/// @brief �N���X���n�߂�
/// @param[in] acf_file �S�̃t�@�C���p�X
void Adx2leLap::Start(const char* acf_file) {
  // �S�̐ݒ�t�@�C���̓o�^
  criAtomEx_RegisterAcfFile(nullptr, acf_file, nullptr, 0);

  // DSP�o�X�ݒ�̓o�^
  criAtomEx_AttachDspBusSetting("DspBusSetting_0", nullptr, 0);

  // �{�C�X�v�[���̍쐬�i�X�g���[���Đ��Ή��j
  CriAtomExStandardVoicePoolConfig vpconfig;
  criAtomExVoicePool_SetDefaultConfigForStandardVoicePool(&vpconfig);
  vpconfig.player_config.streaming_flag = CRI_TRUE;
  _voice_pool = criAtomExVoicePool_AllocateStandardVoicePool(&vpconfig, nullptr, 0);
}

/// @fn End
/// @brief �v���W�F�N�g���I����
void Adx2leLap::End() {
  // �{�C�X�v�[���̉��
  criAtomExVoicePool_Free(_voice_pool);

  // �S�̐ݒ�t�@�C���̓o�^����
  criAtomEx_UnregisterAcf();
}

/// @fn LoadSoundFile
/// @brief �T�E���h�t�@�C���ǂݍ���
/// @param[in] key �T�E���h�f�[�^���ʗp������
/// @param[in] acb ACB�t�@�C���p�X
/// @param[in] acw ACW�t�@�C���p�X
void Adx2leLap::LoadSoundFile(const char* key, const char* acb, const char* awb) {
  CriAtomExAcbHn handle = criAtomExAcb_LoadAcbFile(
    nullptr, acb, nullptr, awb, nullptr, 0);
  _ASSERT_EXPR(_acb_handle_container.count(key) == 0,
    L"Adx2leLap : ���ɓo�^���ꂽ�L�[");
  _acb_handle_container[key] = handle;
}

/// @fn UnloadSoundFile
/// @brief �T�E���h�t�@�C������
/// @param[in] key �T�E���h�f�[�^���ʕ�����
void Adx2leLap::UnloadSoundFile(const char* key) {
  _ASSERT_EXPR(_acb_handle_container.count(key), L"Adx2leLap : �o�^����ĂȂ��L�[");
  CriAtomExAcbHn handle = _acb_handle_container[key];
  _acb_handle_container.erase(key);
  criAtomExAcb_Release(handle);
}

//EOF