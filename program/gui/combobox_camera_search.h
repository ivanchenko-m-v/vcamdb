/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 03-11-2014
///		Date update	: 03-11-2014
///		Comment		:
/// ============================================================================
#ifndef __COMBOBOX_CAMERA_SEARCH_H__
#define __COMBOBOX_CAMERA_SEARCH_H__

#include <QComboBox>
#include <QKeyEvent>

namespace vcamdb
{

class data_camera;
class data_camera_collection;

/// ############################################################################
///			class combobox_camera_search
/// ############################################################################
    class combobox_camera_search : public QComboBox
	{
        Q_OBJECT
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        combobox_camera_search( const combobox_camera_search &rhs );

	public:
        /// --------------------------------------------------------------------
        explicit combobox_camera_search(QWidget *parent = 0);
        /// --------------------------------------------------------------------
        virtual ~combobox_camera_search( );

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
        /// --------------------------------------------------------------------
        const data_camera* camera( ) const;
        /// --------------------------------------------------------------------
        void camera(  const data_camera *cam );
        /// --------------------------------------------------------------------
        const QString &camera_address(int index) const;

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        void initialize( );
        /// --------------------------------------------------------------------
        void clear_data( );
        /// --------------------------------------------------------------------
        void refresh( const QString &text );

	public:

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        combobox_camera_search& operator=( const combobox_camera_search &rhs );

    /// ========================================================================
    ///		EVENTS
    /// ========================================================================
    protected:
        virtual void keyPressEvent( QKeyEvent * e );

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
    private:
        data_camera_collection *_coll_cameras;

    };//class combobox_camera_search
/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace vcamdb
#endif // __COMBOBOX_CAMERA_SEARCH_H__
