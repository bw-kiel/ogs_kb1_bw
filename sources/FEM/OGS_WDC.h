// interface class and wrapper for WDC
// including:
//   parameter lists:  time, indicator, powerrate, targetValue, thresholdValue
//   doublet geometry mesh nodes: warm well1, cold well2, heat exchanger
//
// provides mesh nodes where temperature (and volumetric heat capacity) are measured to balance heat input and output
//
// CSourceTerm::apply_wellDoubletControl

#ifndef OGS_WDC_H
#define OGS_WDC_H


class OGS_WDC;
#include "rf_pcs.h"

#include <list>
#include <utility>
#include <iostream>
#include <stdexcept>
#include <memory>
#include "wellDoubletControl.h"


class OGS_WDC
{
public:
	struct wellDoubletData_t
	{
		struct parameter_group_t
		{
			double time;
			int indicator;
			double powerrate;
			double target_value;
			double threshold_value;
			parameter_group_t(const double& _time, const int& _indicator,
					const double& _powerrate, const double& _target_value, const double& _threshold_value) :
				time(_time), indicator(_indicator), powerrate(_powerrate),
				target_value(_target_value), threshold_value(_threshold_value) {}
			// constructor used with emplace_back below - do not reorder without considering this
		};
		std::list<parameter_group_t> parameter_list;
	};

	struct doublet_mesh_nodes_t
	{	// geometric locations
		long well1_aquifer;
		long well2_aquifer;
		long heatExchanger;
	};

	struct measurement_mesh_nodes_t  // just to wrap return values for update_measurement_mesh_nodes()
	{	// depends on operation type: storing, extracting
		long well1;
		long well2;
	};

private:
	wellDoubletData_t wellDoubletData;
	std::shared_ptr<WellDoubletControl> wellDoubletControl; // JOD 2018-6-27

	bool is_initialized; // new WDC for each new time step - WDC creation is controlled by this flag
	doublet_mesh_nodes_t doublet_mesh_nodes;

	void update_WellDoubletControl(const double& temperature_well1, const double& temperature_well2,
										const double& volumetricHeatCapacity_well1, const double& volumetricHeatCapacity_well2);
	void evaluate_simulation_result(const double& temperature_well1, const double& temperature_well2,
										const double& volumetricHeatCapacity_well1, const double& volumetricHeatCapacity_well2);
public:
	OGS_WDC() : is_initialized(false) {}
	std::shared_ptr<WellDoubletControl> get_WellDoubletControl() const { return wellDoubletControl; }
	const doublet_mesh_nodes_t& get_doublet_mesh_nodes() const { return doublet_mesh_nodes; }
	void discard() { is_initialized = false; }  // must be called, when iteration loop between LIQUID and HEAT has converged

	template<typename... Args>
	void add_parameterGroup(Args&&...args) { wellDoubletData.parameter_list.emplace_back(std::forward<Args>(args) ...); }
	void set_doublet_mesh_nodes(doublet_mesh_nodes_t _doublet_mesh_nodes) { doublet_mesh_nodes = _doublet_mesh_nodes; }  // called in set functions for source terms
	measurement_mesh_nodes_t update_measurement_mesh_nodes(const double& current_time);  // must be called for each new time step (before LIQUID_FLOW runs)
	double get_result(const CRFProcess* m_pcs, const double& temperature_well1, const double& temperature_well2,
			const double& volumetricHeatCapacity_well1, const double& volumetricHeatCapacitywell2);
};


#endif
