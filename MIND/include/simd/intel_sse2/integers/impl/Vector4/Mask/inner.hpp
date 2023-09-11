/**
 * Mask to perform logical operations on Vector4.
 */
class Mask {
    private:
        /** Inner vector of booleans. */
        Int32x4 m_inner ;

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
            const bool& b0,
            const bool& b1,
            const bool& b2,
            const bool& b3
        ) ;

        /**
         * Create from one boolean, applied to all components of the Mask.
         * @param   value   The boolean to apply to all values of the Mask.
         */
        Mask(const bool& value) ;

        /**
         * Create from inner type data.
         * @param   vec     The inner data to copy.
         */
        Mask(const __m128i vec) ;


                                                              /*** UTILITIES ***/
        /**
         * Get values from the mask (unaligned).
         * @param   array   Array in which Mask values are stored.
         * @return  Value in the mask at the given index.
         */
        void get(Array4i& array) ;

        /**
         * Get one value from the mask.
         * @param   index   Index of the value to get (should be lower than
         *                    length).
         * @return  Value in the mask at the given index.
         */
        bool get(const unsigned int& index) ;

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


                                                              /*** OPERATORS ***/
                                                        /** AFFECT OPERATORS **/
        /**
         * Affect the inner value of the Mask to the broadcasted one given as
         * parameter.
         * @param   value   The value to put in the Mask, to all its values.
         * @return  The current Mask once the value is affected to its inner
         *            data.
         */
        Mask& operator=(const bool& value) ;

        /**
         * Affect the inner value to the Mask.
         * @param   vec     The value to put in the Mask.
         * @return  The current Mask once the vec is affected to its inner data.
         */
        Mask& operator=(const __m128i vec) ;

        /**
         * Affect the inner value to the Mask.
         * @param   vec     The value to put in the Mask.
         * @return  The current Mask once the vec is affected to its inner data.
         */
        Mask& operator=(const __m128 vec) ;

                                                            /** CAST OPERATORS **/
        /**
         * Cast the current Mask to its inner data type.
         * @return  The inner data of the Mask.
         */
        operator __m128i() const ;

        /**
         * Cast the current Mask to its inner data type.
         * @return  The inner data of the Mask.
         */
        operator __m128() const ;
} ;
