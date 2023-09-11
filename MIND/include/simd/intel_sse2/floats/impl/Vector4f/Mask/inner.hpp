/**
 * Mask to perform logical operations on Vector4f.
 */
class Mask {
    private:
        /** Inner vector of booleans (as floats). */
        Float32x4 m_inner ;

    public:
        /**
         * Create an empty Mask.
         */
        Mask() ;

        /**
         * Create from four boolean values.
         * @param   b1  First value mask.
         * @param   b2  Second value mask.
         * @param   b3  Third value mask.
         * @param   b4  Fourth value mask.
         */
        Mask(
             const bool b0,
             const bool b1,
             const bool b2,
             const bool b3
            ) ;

        /**
         * Create from one boolean, applied to all components of the Mask.
         * @param   value   The boolean to apply to all values of the Mask.
         */
        Mask(const bool value) ;

        /**
         * Create from inner type data.
         * @param   vec     The inner data to copy.
         */
        Mask(const __m128 vec) ;


        /**
         * Create from a Mask used by integer Vector4.
         * @param   mask    Mask to cast.
         */
        Mask(const Vector4i::Mask& mask) ;

        /**
         * Create from a Mask used by integer Vector4.
         * @param   mask    Mask to cast.
         */
        Mask(const Vector4ui::Mask& mask) ;


                                                              /*** UTILITIES ***/
    public:
        /**
         * Get one value from the mask.
         * @param   index   Index of the value to get (should be lower than
         *                    length).
         * @return  Value in the mask at the given index.
         */
        bool get(const unsigned int index) ;

        /**
         * Get the length of the Mask.
         * @return  The length of the Mask.
         */
        size_t length() const ;


        /**
         * Size of the Mask.
         * @return  The length of the Mask.
         */
        static size_t size() ;

        /**
         * Print the content of the Vector on the console output.
         */
        void print() ;


                                                              /*** OPERATORS ***/
                                                        /** AFFECT OPERATORS **/
        /**
        * Affect the inner value of the Mask to the broadcasted one given as
        * parameter.
         * @param   value   The value to put in the Mask, to all its values.
         * @return  The current Mask once the value is affected to its inner
         *            data.
         */
        Mask& operator=(const bool value) ;

        /**
         * Affect the inner value to the Mask.
         * @param   vec     The value to put in the Mask.
         * @return  The current Mask once the vec is affected to its inner data.
         */
        Mask& operator=(const __m128i& vec) ;

        /**
         * Affect the inner value to the Mask.
         * @param   vec     The value to put in the Mask.
         * @return  The current Mask once the vec is affected to its inner data.
         */
        Mask& operator=(const __m128 vec) ;

        /**
         * Affect the inner value to the Mask.
         * @param   mask    The value to put in the Mask.
         * @return  The current Mask once the vec is affected to its inner data.
         */
        Mask& operator=(const Vector4i::Mask& mask) ;

                                                            /** CAST OPERATORS **/
        /**
         * Cast the current Mask to its inner data type.
         * @return  The inner data of the Mask.
         */
        explicit operator __m128i() const ;

        /**
         * Cast the current Mask to a __m128.
         * @return  The inner data of the Mask as a __m128 vector.
         */
        operator __m128() const ;

        /**
         * Cast the current Mask to a Vector4i::Mask.
         * @return  The Vector4i::Mask version of the current Mask.
         */
        explicit operator Vector4i::Mask() const ;

        /**
         * Cast the current Mask to a Vector4ui::Mask.
         * @return  The Vector4ui::Mask version of the current Mask.
         * @warning Be careful with negative values.
         */
        explicit operator Vector4ui::Mask() const ;
} ;
