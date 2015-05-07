#pragma once

namespace wand3d {
  class WandData;
  namespace utils {
    /**
     * @brief          Constructs a OpenGL rotation matrix from WandData.
     * @param[in]  data    Reference to WandData struct populated with target data.
     * @param[out]  gl_matrix  OpenGL matrix as float array (column first order).
     */
    void getGLRotMatrix(const WandData& data, float gl_matrix[16]);

    /**
     * @brief          Constructs a OpenGL translation matrix from WandData.
     * @param[in]  data    Reference to WandData struct populated with target data.
     * @param[out]  gl_matrix  OpenGL matrix as float array (column first order).
     */
    void getGLTransMatrix(const WandData& data, float gl_matrix[16]);

    /**
     * @brief          Constructs a OpenGL rotation and translation matrix from WandData.
     * @param[in]  data    Reference to WandData struct populated with target data.
     * @param[out]  gl_matrix  OpenGL matrix as float array (column first order).
     */
    void getGLRotTransMatrix(const WandData& data, float gl_matrix[16]);
  }
}
