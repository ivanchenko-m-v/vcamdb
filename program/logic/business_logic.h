/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 05-10-2014
///		Date update	: 18-02-2015
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
class data_model_object_type;
class data_model_violation_type;
class data_model_contractor;

class data_camera;
class data_camera_collection;
class data_violation_object_collection;
class data_violation;
class data_violation_collection;
class data_contractor_collection;
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
            _model_camera_object(0),
            _model_object_type(0),
            _model_violation_type(0),
            _model_contractor(0)
		{ }

	/// ========================================================================
	///		PROPERTIES
	/// ========================================================================
	public:
    /// ------------------------------------------------------------------------
        const QString& db_path( ) const
        { return this->_db_path; }

        void db_path( const QString& db_path )
        { this->_db_path = db_path; }

    /// ------------------------------------------------------------------------
        const QString& db_ex_path( ) const
        { return this->_db_ex_path; }

        void db_ex_path( const QString& db_ex_path )
        { this->_db_ex_path = db_ex_path; }
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
    /// ------------------------------------------------------------------------
        data_model_object_type* model_object_type( ) const
        { return this->_model_object_type; }
    /// ------------------------------------------------------------------------
        data_model_violation_type* model_violation_type( ) const
        { return this->_model_violation_type; }
    /// ------------------------------------------------------------------------
        data_model_contractor* model_contractor( ) const
        { return this->_model_contractor; }

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
        void init_model_object_type( );
    /// ------------------------------------------------------------------------
        void init_model_violation_type( );
    /// ------------------------------------------------------------------------
        void init_model_contractor( );
    /// ------------------------------------------------------------------------
        void free_memory( );

	public:
	/// ------------------------------------------------------------------------
		void init( );
	/// ------------------------------------------------------------------------
		void exit( );

    /// ------------------------------------------------------------------------
        void object_type_select( );
    /// ------------------------------------------------------------------------
        void violation_type_select( );
    /// ------------------------------------------------------------------------
        data_camera_collection* camera_select(const QString &s_filter);
    /// ------------------------------------------------------------------------
        data_camera *camera_select_one(const QString &s_filter);
    /// ------------------------------------------------------------------------
        data_violation_object_collection*
                               violation_object_select(
                                                        const QString &s_type,
                                                        const QString &s_filter
                                                      );
    /// ------------------------------------------------------------------------
        data_contractor_collection*
                               contractor_select(
                                                 const QString &s_object_type,
                                                 const QString &s_filter
                                                );
    /// ------------------------------------------------------------------------
        data_violation_object_collection* CA_select( const QString &s_filter );
    /// ------------------------------------------------------------------------
        data_violation_object_collection* DT_select( const QString &s_filter );
    /// ------------------------------------------------------------------------
        data_violation_object_collection* ODH_select( const QString &s_filter );
    /// ------------------------------------------------------------------------
        void violation_insert( const data_violation &record );
    /// ------------------------------------------------------------------------
        void violation_update( const data_violation &record );
    /// ------------------------------------------------------------------------
        void violation_delete( const data_violation &record );
    /// ------------------------------------------------------------------------
        void violation_select( );
    /// ------------------------------------------------------------------------
        void ODH_import( const QString &f_file_from );
    /// ------------------------------------------------------------------------
        void DT_import( const QString &f_file_from );
    /// ------------------------------------------------------------------------
        void CA_import( const QString &f_file_from );

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
        QString _db_ex_path;

        data_model_cam_selection    *_model_cam_selection;
        data_model_violation        *_model_violation;
        data_model_camera           *_model_camera;
        data_model_camera_object    *_model_camera_object;
        data_model_object_type      *_model_object_type;
        data_model_violation_type   *_model_violation_type;
        data_model_contractor       *_model_contractor;

	};//class business_logic

/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace vcamdb

#endif // __BUSINESS_LOGIC_H__
