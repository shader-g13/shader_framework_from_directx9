#include <stdio.h>

#include <cri_adx2le.h>
#pragma comment(lib, "cri_ware_pcx86_LE_import.lib")
#define ACF_FILE ("res/adx/Test.acf")
#define ACB_FILE ("res/adx/CueSheetTest.acb")

/// @brief �G���[�R�[���o�b�N�֐��̃��[�U����
static void user_error_callback_func(const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray) {
  const CriChar8 *errmsg;
  /* �G���[�R�[�h����G���[������ɕϊ����ăR���\�[���o�͂��� */
  errmsg = criErr_ConvertIdToMessage(errid, p1, p2);
  OutputDebugString(errmsg);
  return;
}

/// @brief �������m�ۊ֐��̃��[�U����
void *user_alloc_func(void *obj, CriUint32 size) {
  void *ptr;
  ptr = malloc(size);
  return ptr;
}

/// @brief ����������֐��̃��[�U����
void user_free_func(void *obj, void *ptr) {
  free(ptr);
}

void main() {

  CriAtomExVoicePoolHn voice_pool;   // �{�C�X�v�[���n���h��
  CriAtomDbasId dbas;                // D-BAS�n���h��

  // �G���[�R�[���o�b�N�֐��̓o�^
  criErr_SetCallback(user_error_callback_func);

  // �������A���P�[�^�̓o�^
  criAtomEx_SetUserAllocator(user_alloc_func, user_free_func, NULL);

  // ���C�u����������
  criAtomEx_Initialize_PC(NULL, NULL, 0);

  // �X�g���[�~���O�p�o�b�t�@�̍쐬
  dbas = criAtomDbas_Create(NULL, NULL, 0);

  // �S�̐ݒ�t�@�C���̓o�^
  criAtomEx_RegisterAcfFile(NULL, ACF_FILE, NULL, 0);

  // DSP�o�X�ݒ�̓o�^
  criAtomEx_AttachDspBusSetting("DspBusSetting_0", NULL, 0);

  // �{�C�X�v�[���̍쐬�i�X�g���[���Đ��Ή��j
  CriAtomExStandardVoicePoolConfig vpconfig;
  criAtomExVoicePool_SetDefaultConfigForStandardVoicePool(&vpconfig);
  vpconfig.player_config.streaming_flag = CRI_TRUE;
  voice_pool = criAtomExVoicePool_AllocateStandardVoicePool(&vpconfig, NULL, 0);
  // MEMO: �X�g���[���Đ������Ȃ�A�{�C�X�v�[���͍\����NULL�w��ŉ�


  CriAtomExAcbHn acb_hn;             // ACB�n���h��

  /* �T�E���h�f�[�^�̓ǂݍ��� */
  acb_hn = criAtomExAcb_LoadAcbFile(NULL, ACB_FILE, nullptr, NULL, NULL, 0);

  CriAtomExPlayerHn player;          // �v���[���n���h��
  // �v���[���n���h���̍쐬
  player = criAtomExPlayer_Create(NULL, NULL, 0);

  // �L���[�̎w��
  criAtomExPlayer_SetCueId(player, acb_hn, 0);
  // �L���[�̍Đ��J�n
  criAtomExPlayer_Start(player);


  CriAtomExPlaybackId playback_id;

  // �L���[�Đ��ƃv���C�o�b�NID�̋L�^
  criAtomExPlayer_SetCueId(player, acb_hn, 0);
  playback_id = criAtomExPlayer_Start(player);

  auto msec = criAtomExPlayback_GetTime(playback_id);
  for (; msec < 10000;) {

    // �Đ������̎擾
    msec = criAtomExPlayback_GetTime(playback_id);

    // �Đ��I���̔���
    if (criAtomExPlayback_GetStatus(playback_id) == CRIATOMEXPLAYBACK_STATUS_REMOVED) {
      // �Đ��I��
    }



    printf("%dmsec\n", msec);

    /* ADX2�T�[�o�����̎��s */
    criAtomEx_ExecuteMain();
  }

  /* �v���[���n���h���̔j�� */
  criAtomExPlayer_Destroy(player);

  /* ACB�n���h���̉�� */
  criAtomExAcb_Release(acb_hn);

  /* �{�C�X�v�[���̉�� */
  criAtomExVoicePool_Free(voice_pool);

  /* �S�̐ݒ�t�@�C���̓o�^���� */
  criAtomEx_UnregisterAcf();

  /* ���C�u�����̏I�� */
  criAtomEx_Finalize_PC();

}