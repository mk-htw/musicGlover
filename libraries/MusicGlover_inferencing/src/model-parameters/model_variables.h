/* Generated by Edge Impulse
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _EI_CLASSIFIER_MODEL_VARIABLES_H_
#define _EI_CLASSIFIER_MODEL_VARIABLES_H_

#include <stdint.h>
#include "model_metadata.h"

#include "tflite-model/tflite_learn_8_compiled.h"
#include "edge-impulse-sdk/classifier/ei_model_types.h"
#include "edge-impulse-sdk/classifier/inferencing_engines/engines.h"

const char* ei_classifier_inferencing_categories[] = { "mute_unmute", "next", "play_pause", "previous", "volume_down", "volume_up" };

uint8_t ei_dsp_config_4_axes[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
const uint32_t ei_dsp_config_4_axes_size = 9;
ei_dsp_config_spectral_analysis_t ei_dsp_config_4 = {
    4, // uint32_t blockId
    4, // int implementationVersion
    9, // int length of axes
    1.0f, // float scale-axes
    1, // int input-decimation-ratio
    "low", // select filter-type
    3.0f, // float filter-cutoff
    6, // int filter-order
    "FFT", // select analysis-type
    16, // int fft-length
    3, // int spectral-peaks-count
    0.1f, // float spectral-peaks-threshold
    "0.1, 0.5, 1.0, 2.0, 5.0", // string spectral-power-edges
    true, // boolean do-log
    true, // boolean do-fft-overlap
    1, // int wavelet-level
    "db4", // select wavelet
    false // boolean extra-low-freq
};

const size_t ei_dsp_blocks_size = 1;
ei_model_dsp_t ei_dsp_blocks[ei_dsp_blocks_size] = {
    { // DSP block 4
        4,
        54, // output size
        &extract_spectral_analysis_features, // DSP function pointer
        (void*)&ei_dsp_config_4, // pointer to config struct
        ei_dsp_config_4_axes, // array of offsets into the input stream, one for each axis
        ei_dsp_config_4_axes_size, // number of axes
        1, // version
        nullptr, // factory function
    }
};
const ei_config_tflite_eon_graph_t ei_config_tflite_graph_8 = {
    .implementation_version = 1,
    .model_init = &tflite_learn_8_init,
    .model_invoke = &tflite_learn_8_invoke,
    .model_reset = &tflite_learn_8_reset,
    .model_input = &tflite_learn_8_input,
    .model_output = &tflite_learn_8_output,
};

const ei_learning_block_config_tflite_graph_t ei_learning_block_config_8 = {
    .implementation_version = 1,
    .classification_mode = EI_CLASSIFIER_CLASSIFICATION_MODE_CLASSIFICATION,
    .block_id = 8,
    .object_detection = 0,
    .object_detection_last_layer = EI_CLASSIFIER_LAST_LAYER_UNKNOWN,
    .output_data_tensor = 0,
    .output_labels_tensor = 1,
    .output_score_tensor = 2,
    .threshold = 0,
    .quantized = 1,
    .compiled = 1,
    .graph_config = (void*)&ei_config_tflite_graph_8
};

const size_t ei_learning_blocks_size = 1;
const uint32_t ei_learning_block_8_inputs[1] = { 4 };
const uint32_t ei_learning_block_8_inputs_size = 1;
const ei_learning_block_t ei_learning_blocks[ei_learning_blocks_size] = {
    {
        8,
        false,
        &run_nn_inference,
        (void*)&ei_learning_block_config_8,
        EI_CLASSIFIER_IMAGE_SCALING_NONE,
        ei_learning_block_8_inputs,
        ei_learning_block_8_inputs_size,
        6
    },
};

const ei_model_performance_calibration_t ei_calibration = {
    1, /* integer version number */
    false, /* has configured performance calibration */
    (int32_t)(EI_CLASSIFIER_RAW_SAMPLE_COUNT / ((EI_CLASSIFIER_FREQUENCY > 0) ? EI_CLASSIFIER_FREQUENCY : 1)) * 1000, /* Model window */
    0.8f, /* Default threshold */
    (int32_t)(EI_CLASSIFIER_RAW_SAMPLE_COUNT / ((EI_CLASSIFIER_FREQUENCY > 0) ? EI_CLASSIFIER_FREQUENCY : 1)) * 500, /* Half of model window */
    0   /* Don't use flags */
};
const ei_object_detection_nms_config_t ei_object_detection_nms = {
    0.0f, /* NMS confidence threshold */
    0.2f  /* NMS IOU threshold */
};

const ei_impulse_t impulse_366282_0 = {
    .project_id = 366282,
    .project_owner = "HTW Berlin",
    .project_name = "MusicGlover",
    .deploy_version = 4,

    .nn_input_frame_size = 54,
    .raw_sample_count = 156,
    .raw_samples_per_frame = 9,
    .dsp_input_frame_size = 156 * 9,
    .input_width = 0,
    .input_height = 0,
    .input_frames = 0,
    .interval_ms = 16,
    .frequency = 62.5,
    .dsp_blocks_size = ei_dsp_blocks_size,
    .dsp_blocks = ei_dsp_blocks,
    
    .object_detection_count = 0,
    .fomo_output_size = 0,
    
    .tflite_output_features_count = 6,
    .learning_blocks_size = ei_learning_blocks_size,
    .learning_blocks = ei_learning_blocks,

    .inferencing_engine = EI_CLASSIFIER_TFLITE,

    .sensor = EI_CLASSIFIER_SENSOR_FUSION,
    .fusion_string = "accX + accY + accZ + gyrX + gyrY + gyrZ + magX + magY + magZ",
    .slice_size = (156/4),
    .slices_per_model_window = 4,

    .has_anomaly = EI_ANOMALY_TYPE_UNKNOWN,
    .label_count = 6,
    .calibration = ei_calibration,
    .categories = ei_classifier_inferencing_categories,
    .object_detection_nms = ei_object_detection_nms
};

ei_impulse_handle_t impulse_handle_366282_0 = ei_impulse_handle_t( &impulse_366282_0 );
ei_impulse_handle_t& ei_default_impulse = impulse_handle_366282_0;

#endif // _EI_CLASSIFIER_MODEL_METADATA_H_
