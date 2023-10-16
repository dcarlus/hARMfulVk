/// <summary>
/// Mask to perform logical operations on Vector4f.
/// </summary>
class Mask {
    private:
        /// <summary>
        /// Inner vector of booleans (as floats).
        /// </summary>
        Float32x4 m_inner ;

    public:
        /// <summary>
        /// Create an empty Mask.
        /// </summary>
        Mask() ;

        /// <summary>
        /// Create from four boolean values.
        /// </summary>
        /// <param name="b0">First value mask.</param>
        /// <param name="b1">Second value mask.</param>
        /// <param name="b2">Third value mask.</param>
        /// <param name="b3">Fourth value mask.</param>
        Mask(
             const bool b0,
             const bool b1,
             const bool b2,
             const bool b3
            ) ;

        /// <summary>
        /// Create from one boolean, applied to all components of the Mask.
        /// </summary>
        /// <param name="value">
        /// The boolean to apply to all values of the Mask.
        /// </param>
        Mask(const bool value) ;

        /// <summary>
        /// Create from inner type data.
        /// </summary>
        /// <param name="vec">The inner data to copy.</param>
        Mask(const __m128 vec) ;

        /// <summary>
        /// Create from a Mask used by integer Vector4.
        /// </summary>
        /// <param name="mask">Mask to cast.</param>
        Mask(const Vector4i::Mask& mask) ;

        /// <summary>
        /// Create from a Mask used by integer Vector4.
        /// </summary>
        /// <param name="mask">Mask to cast.</param>
        Mask(const Vector4ui::Mask& mask) ;

    public:
        /// <summary>
        /// Get one value from the mask.
        /// </summary>
        /// <param name="index">
        /// Index of the value to get (should be lower than length).
        /// </param>
        /// <returns>Value in the mask at the given index.</returns>
        bool get(const unsigned int index) ;

        /// <summary>
        /// Get the length of the Mask.
        /// </summary>
        /// <returns>The length of the Mask.</returns>
        size_t length() const ;

        /// <summary>
        /// Size of the Mask.
        /// </summary>
        /// <returns>The length of the Mask.</returns>
        static size_t size() ;

        /// <summary>
        /// Print the content of the Vector on the console output.
        /// </summary>
        void print() ;

        /// <summary>
        /// Affect the inner value of the Mask to the broadcasted one given as
        /// parameter.
        /// </summary>
        /// <param name="value">
        /// The value to put in the Mask, to all its values.
        /// </param>
        /// <returns>
        /// The current Mask once the value is affected to its inner data.
        /// </returns>
        Mask& operator=(const bool value) ;

        /// <summary>
        /// Affect the inner value to the Mask.
        /// </summary>
        /// <param name="vec">The value to put in the Mask.</param>
        /// <returns>
        /// The current Mask once the vec is affected to its inner data.
        /// </returns>
        Mask& operator=(const __m128i& vec) ;

        /// <summary>
        /// Affect the inner value to the Mask.
        /// </summary>
        /// <param name="vec">The value to put in the Mask.</param>
        /// <returns>
        /// The current Mask once the vec is affected to its inner data.
        /// </returns>
        Mask& operator=(const __m128 vec) ;

        /// <summary>
        /// Affect the inner value to the Mask.
        /// </summary>
        /// <param name="mask">The value to put in the Mask.</param>
        /// <returns>
        /// The current Mask once the vec is affected to its inner data.
        /// </returns>
        Mask& operator=(const Vector4i::Mask& mask) ;

        /// <summary>
        /// Cast the current Mask to its inner data type.
        /// </summary>
        explicit operator __m128i() const ;

        /// <summary>
        /// Cast the current Mask to a __m128.
        /// </summary>
        operator __m128() const ;

        /// <summary>
        /// Cast the current Mask to a Vector4i::Mask.
        /// </summary>
        explicit operator Vector4i::Mask() const ;

        /// <summary>
        /// Cast the current Mask to a Vector4ui::Mask.
        /// </summary>
        /// <remarks>
        /// Be careful with negative values.
        /// </remarks>
        explicit operator Vector4ui::Mask() const ;
} ;
