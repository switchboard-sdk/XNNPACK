// Auto-generated file. Do not edit!
//   Template: src/qs8-gemm/MRx4c2-sse.c.in
//   Generator: tools/xngen
//
// Copyright 2020 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <smmintrin.h>

#include <xnnpack/gemm.h>
#include <xnnpack/math.h>


void xnn_qs8_gemm_minmax_gemmlowp_ukernel_2x4c2__sse41_ld64(
    size_t mr,
    size_t nc,
    size_t kc,
    const int8_t* restrict a,
    size_t a_stride,
    const void* restrict w,
    int8_t* restrict c,
    size_t cm_stride,
    size_t cn_stride,
    const union xnn_qs8_conv_minmax_params params[restrict XNN_MIN_ELEMENTS(1)]) XNN_DISABLE_TSAN XNN_DISABLE_MSAN
{
  assert(mr != 0);
  assert(mr <= 2);
  assert(nc != 0);
  assert(kc != 0);
  assert(kc % sizeof(int8_t) == 0);
  assert(a != NULL);
  assert(w != NULL);
  assert(c != NULL);

  kc = round_up_po2(kc, 2);
  const int8_t* a0 = a;
  int8_t* c0 = c;
  const int8_t* a1 = (const int8_t*) ((uintptr_t) a0 + a_stride);
  int8_t* c1 = (int8_t*) ((uintptr_t) c0 + cm_stride);
  if XNN_UNPREDICTABLE(mr != 2) {
    a1 = a0;
    c1 = c0;
  }

  do {
    __m128i vacc0x0123 = _mm_loadu_si128((const __m128i*) w);
    __m128i vacc1x0123 = vacc0x0123;
    w = (const void*) ((uintptr_t) w + 4 * sizeof(int32_t));

    size_t k = kc;
    while (k >= 8 * sizeof(int8_t)) {
      const __m128i va0 = _mm_loadl_epi64((const __m128i*) a0);
      const __m128i vxa0 = _mm_cvtepi8_epi16(va0);
      a0 += 8;
      const __m128i va1 = _mm_loadl_epi64((const __m128i*) a1);
      const __m128i vxa1 = _mm_cvtepi8_epi16(va1);
      a1 += 8;

      const __m128i vb0 = _mm_loadl_epi64((const __m128i*) w);
      const __m128i vxb0 = _mm_cvtepi8_epi16(vb0);

      vacc0x0123 = _mm_add_epi32(vacc0x0123,
        _mm_madd_epi16(_mm_shuffle_epi32(vxa0, _MM_SHUFFLE(0, 0, 0, 0)), vxb0));
      vacc1x0123 = _mm_add_epi32(vacc1x0123,
        _mm_madd_epi16(_mm_shuffle_epi32(vxa1, _MM_SHUFFLE(0, 0, 0, 0)), vxb0));
      const __m128i vb1 = _mm_loadl_epi64((const __m128i*) ((uintptr_t) w + 8 * sizeof(int8_t)));
      const __m128i vxb1 = _mm_cvtepi8_epi16(vb1);

      vacc0x0123 = _mm_add_epi32(vacc0x0123,
        _mm_madd_epi16(_mm_shuffle_epi32(vxa0, _MM_SHUFFLE(1, 1, 1, 1)), vxb1));
      vacc1x0123 = _mm_add_epi32(vacc1x0123,
        _mm_madd_epi16(_mm_shuffle_epi32(vxa1, _MM_SHUFFLE(1, 1, 1, 1)), vxb1));
      const __m128i vb2 = _mm_loadl_epi64((const __m128i*) ((uintptr_t) w + 16 * sizeof(int8_t)));
      const __m128i vxb2 = _mm_cvtepi8_epi16(vb2);

      vacc0x0123 = _mm_add_epi32(vacc0x0123,
        _mm_madd_epi16(_mm_shuffle_epi32(vxa0, _MM_SHUFFLE(2, 2, 2, 2)), vxb2));
      vacc1x0123 = _mm_add_epi32(vacc1x0123,
        _mm_madd_epi16(_mm_shuffle_epi32(vxa1, _MM_SHUFFLE(2, 2, 2, 2)), vxb2));
      const __m128i vb3 = _mm_loadl_epi64((const __m128i*) ((uintptr_t) w + 24 * sizeof(int8_t)));
      const __m128i vxb3 = _mm_cvtepi8_epi16(vb3);

      vacc0x0123 = _mm_add_epi32(vacc0x0123,
        _mm_madd_epi16(_mm_shuffle_epi32(vxa0, _MM_SHUFFLE(3, 3, 3, 3)), vxb3));
      vacc1x0123 = _mm_add_epi32(vacc1x0123,
        _mm_madd_epi16(_mm_shuffle_epi32(vxa1, _MM_SHUFFLE(3, 3, 3, 3)), vxb3));

      w = (const void*) ((uintptr_t) w + 32 * sizeof(int8_t));
      k -= 8 * sizeof(int8_t);
    }
    if (k != 0) {
      const __m128i va0 = _mm_loadl_epi64((const __m128i*) a0);
      const __m128i vxa0 = _mm_cvtepi8_epi16(va0);
      a0 = (const int8_t*) ((uintptr_t) a0 + k);
      const __m128i va1 = _mm_loadl_epi64((const __m128i*) a1);
      const __m128i vxa1 = _mm_cvtepi8_epi16(va1);
      a1 = (const int8_t*) ((uintptr_t) a1 + k);

      const __m128i vb0 = _mm_loadl_epi64((const __m128i*) w);
      const __m128i vxb0 = _mm_cvtepi8_epi16(vb0);
      w = (const void*) ((uintptr_t) w + 8 * sizeof(int8_t));

      vacc0x0123 = _mm_add_epi32(vacc0x0123,
        _mm_madd_epi16(_mm_shuffle_epi32(vxa0, _MM_SHUFFLE(0, 0, 0, 0)), vxb0));
      vacc1x0123 = _mm_add_epi32(vacc1x0123,
        _mm_madd_epi16(_mm_shuffle_epi32(vxa1, _MM_SHUFFLE(0, 0, 0, 0)), vxb0));

      if (k > 2 * sizeof(int8_t)) {
        const __m128i vb1 = _mm_loadl_epi64((const __m128i*) w);
        const __m128i vxb1 = _mm_cvtepi8_epi16(vb1);
        w = (const void*) ((uintptr_t) w + 8 * sizeof(int8_t));

        vacc0x0123 = _mm_add_epi32(vacc0x0123,
          _mm_madd_epi16(_mm_shuffle_epi32(vxa0, _MM_SHUFFLE(1, 1, 1, 1)), vxb1));
        vacc1x0123 = _mm_add_epi32(vacc1x0123,
          _mm_madd_epi16(_mm_shuffle_epi32(vxa1, _MM_SHUFFLE(1, 1, 1, 1)), vxb1));

        if (k > 4 * sizeof(int8_t)) {
          const __m128i vb2 = _mm_loadl_epi64((const __m128i*) w);
          const __m128i vxb2 = _mm_cvtepi8_epi16(vb2);
          w = (const void*) ((uintptr_t) w + 8 * sizeof(int8_t));

          vacc0x0123 = _mm_add_epi32(vacc0x0123,
            _mm_madd_epi16(_mm_shuffle_epi32(vxa0, _MM_SHUFFLE(2, 2, 2, 2)), vxb2));
          vacc1x0123 = _mm_add_epi32(vacc1x0123,
            _mm_madd_epi16(_mm_shuffle_epi32(vxa1, _MM_SHUFFLE(2, 2, 2, 2)), vxb2));
        }
      }
    }

    const __m128i vmultiplier = _mm_load_si128((const __m128i*) params->gemmlowp_sse4.multiplier);
    const __m128i vrounding = _mm_load_si128((const __m128i*) params->gemmlowp_sse4.rounding);

    const __m128i vacc0x1133 = _mm_shuffle_epi32(vacc0x0123, _MM_SHUFFLE(3, 3, 1, 1));
    const __m128i vacc1x1133 = _mm_shuffle_epi32(vacc1x0123, _MM_SHUFFLE(3, 3, 1, 1));

    const __m128i vprod0x02 = _mm_add_epi64(_mm_mul_epi32(vacc0x0123, vmultiplier), vrounding);
    const __m128i vprod1x02 = _mm_add_epi64(_mm_mul_epi32(vacc1x0123, vmultiplier), vrounding);

    const __m128i vprod0x13 = _mm_add_epi64(_mm_mul_epi32(vacc0x1133, vmultiplier), vrounding);
    const __m128i vprod1x13 = _mm_add_epi64(_mm_mul_epi32(vacc1x1133, vmultiplier), vrounding);

    const __m128i vq31prod0x02 = _mm_srli_epi64(vprod0x02, 31);
    const __m128i vq31prod0x13 = _mm_add_epi64(vprod0x13, vprod0x13);
    const __m128i vq31prod1x02 = _mm_srli_epi64(vprod1x02, 31);
    const __m128i vq31prod1x13 = _mm_add_epi64(vprod1x13, vprod1x13);

    const __m128i vq31prod0x0123 = _mm_blend_epi16(vq31prod0x02, vq31prod0x13, 0xCC);
    const __m128i vq31prod1x0123 = _mm_blend_epi16(vq31prod1x02, vq31prod1x13, 0xCC);

    const __m128i vremainder_mask = _mm_load_si128((const __m128i*) params->gemmlowp_sse4.remainder_mask);
    const __m128i vrem0x0123 =
      _mm_add_epi32(_mm_and_si128(vq31prod0x0123, vremainder_mask), _mm_cmpgt_epi32(_mm_setzero_si128(), vq31prod0x0123));
    const __m128i vrem1x0123 =
      _mm_add_epi32(_mm_and_si128(vq31prod1x0123, vremainder_mask), _mm_cmpgt_epi32(_mm_setzero_si128(), vq31prod1x0123));

    const __m128i vremainder_threshold = _mm_load_si128((const __m128i*) params->gemmlowp_sse4.remainder_threshold);
    const __m128i vshift = _mm_load_si128((const __m128i*) params->gemmlowp_sse4.shift);
    vacc0x0123 =
      _mm_sub_epi32(_mm_sra_epi32(vq31prod0x0123, vshift), _mm_cmpgt_epi32(vrem0x0123, vremainder_threshold));
    vacc1x0123 =
      _mm_sub_epi32(_mm_sra_epi32(vq31prod1x0123, vshift), _mm_cmpgt_epi32(vrem1x0123, vremainder_threshold));

    const __m128i voutput_zero_point = _mm_load_si128((const __m128i*) params->gemmlowp_sse4.output_zero_point);
    __m128i vacc01x0123 = _mm_adds_epi16(_mm_packs_epi32(vacc0x0123, vacc1x0123), voutput_zero_point);


    __m128i vout = _mm_packs_epi16(vacc01x0123, vacc01x0123);

    vout = _mm_max_epi8(vout, _mm_load_si128((const __m128i*) params->gemmlowp_sse4.output_min));
    vout = _mm_min_epi8(vout, _mm_load_si128((const __m128i*) params->gemmlowp_sse4.output_max));

    if (nc >= 4) {
      *((uint32_t*) c0) = (uint32_t) _mm_cvtsi128_si32(vout);
      *((uint32_t*) c1) = (uint32_t) _mm_extract_epi32(vout, 1);

      c0 = (int8_t*) ((uintptr_t) c0 + cn_stride);
      c1 = (int8_t*) ((uintptr_t) c1 + cn_stride);

      a0 = (const int8_t*) ((uintptr_t) a0 - kc);
      a1 = (const int8_t*) ((uintptr_t) a1 - kc);

      nc -= 4;
    } else {
      if (nc & 2) {
        *((uint16_t*) c0) = (uint16_t) _mm_extract_epi16(vout, 0);
        c0 += 2;
        *((uint16_t*) c1) = (uint16_t) _mm_extract_epi16(vout, 2);
        c1 += 2;
        vout = _mm_srli_epi32(vout, 16);
      }
      if (nc & 1) {
        *((int8_t*) c0) = (int8_t) _mm_extract_epi8(vout, 0);
        *((int8_t*) c1) = (int8_t) _mm_extract_epi8(vout, 4);
      }

      nc = 0;
    }
  } while (nc != 0);
}
