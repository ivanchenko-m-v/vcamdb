/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 05-10-2014
///		Date update	: 14-10-2014
///		Comment		:
/// ============================================================================
#ifndef __BUSINESS_LOGIC_H__
#define __BUSINESS_LOGIC_H__

#include "application.h"
#include <QDate>

namespace vcamdb
{

class data_model_cam_selection;
class data_model_violation;
class data_model_camera;
class data_model_camera_object;
/// ############################################################################
///			class business_logic
/// ############################################################################
	class business_logic
	{
	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================
	private:
	/// ------------------------------------------------------------------------
		business_logic( const business_logic &rhs );

	public:
	/// ------------------------------------------------------------------------
		business_logic( ) :
            _db_path(""),
            _model_cam_selection(0),
            _model_violation(0),
            _model_camera(0),
            _model_camera_object(0)
		{ }

	/// ========================================================================
	///		PROPERTIES
	/// ========================================================================
	public:
    /// ------------------------------------------------------------------------
        const QString& db_path( ) const
        { return this->_db_path; }

        void db_path( const QString& db_path)
        { this->_db_path = db_path; }
    /// ------------------------------------------------------------------------
        data_model_cam_selection* model_cam_selection( ) const
        { return this->_model_cam_selection; }
    /// ------------------------------------------------------------------------
        data_model_violation* model_violation( ) const
        { return this->_model_violation; }
    /// ------------------------------------------------------------------------
        data_model_camera* model_camera( ) const
        { return this->_model_camera; }
    /// ------------------------------------------------------------------------
        data_model_camera_object* model_camera_object( ) const
        { return this->_model_camera_object; }

    /// ========================================================================
	///		FUNCTIONS
	/// ========================================================================
	private:
	/// ------------------------------------------------------------------------
        void init_data_models( );
	/// ------------------------------------------------------------------------
        void init_model_cam_selection( );
    /// ------------------------------------------------------------------------
        void init_model_violation( );
    /// ------------------------------------------------------------------------
        void init_model_camera( );
    /// ------------------------------------------------------------------------
        void init_model_camera_object( );
    /// ------------------------------------------------------------------------
        void free_memory( );

	public:
	/// ------------------------------------------------------------------------
		void init( );
	/// ------------------------------------------------------------------------
		void exit( );

	/// ========================================================================
	///		OPERATORS
	/// ========================================================================
	private:
		business_logic& operator=( const business_logic &rhs );

	public:

	/// ========================================================================
	///		FIELDS
    /// ========================================================================
    private:
        QString _db_path;

        data_model_cam_selection    *_model_cam_selection;
        data_model_violation        *_model_violation;
        data_model_camera           *_model_camera;
        data_model_camera_object    *_model_camera_object;

	};//class business_logic

/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace vcamdb

#endif // __BUSINESS_LOGIC_H__
