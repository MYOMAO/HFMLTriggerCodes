#include "HFMLTriggerInterface.h"

#include <fun4all/Fun4AllReturnCodes.h>
#include <pdbcalbase/PdbParameterMap.h>
#include <phool/PHCompositeNode.h>
#include <phool/PHTimeServer.h>
#include <phool/PHTimer.h>
#include <phool/getClass.h>

#include <phool/PHCompositeNode.h>

#include <g4main/PHG4Hit.h>
#include <g4main/PHG4Particle.h>
#include <g4main/PHG4HitContainer.h>
#include <g4main/PHG4TruthInfoContainer.h>

#include <trackbase/TrkrHitTruthAssocv1.h>
#include <trackbase/TrkrHitSetContainer.h>
//#include <trackbase/TrkrClusterHitAssoc.h>
#include <trackbase/TrkrHitSet.h>
#include <trackbase/TrkrHit.h>
//#include <trackbase/TrkrCluster.h>

#include <mvtx/MvtxDefs.h>
#include <mvtx/CylinderGeom_Mvtx.h>

#include <intt/InttDefs.h>
#include <intt/CylinderGeomIntt.h>

#include <g4detectors/PHG4Cell.h>
#include <g4detectors/PHG4CellContainer.h>
#include <g4detectors/PHG4CylinderCellGeom.h>
#include <g4detectors/PHG4CylinderCellGeomContainer.h>
#include <g4detectors/PHG4CylinderGeom.h>
#include <g4detectors/PHG4CylinderGeomContainer.h>

//#include <g4eval/SvtxEvalStack.h>

#include <HepMC/GenEvent.h>
#include <HepMC/GenVertex.h>
#include <phhepmc/PHHepMCGenEvent.h>
#include <phhepmc/PHHepMCGenEventMap.h>

#include <TDatabasePDG.h>
#include <TFile.h>
#include <TH2F.h>
#include <TH3F.h>
#include <TLorentzVector.h>
#include <TString.h>
#include <TTree.h>

#include <rapidjson/document.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/prettywriter.h>

#include <boost/format.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>


#include <cassert>
#include <cmath>
#include <cstddef>
#include <iostream>

using namespace std;

HFMLTriggerInterface::HFMLTriggerInterface(std::string filename)
	: SubsysReco("HFMLTriggerInterface")
	, _ievent(0)
	, _f(nullptr)
	, _eta_min(-1)
	, _eta_max(1)
	, _embedding_id(1)
	, _nlayers_maps(3)
	, m_hitsets(nullptr)
	, m_GenEventMap(nullptr)
	, m_truthInfo(nullptr)
	  , m_g4hits_mvtx(nullptr)
	  //	, _svtxevalstack(nullptr)
	, m_hit_truth_map(nullptr)
	, m_Flags(nullptr)
	, m_Geoms(nullptr)
	, m_hitStaveLayer(nullptr)
	, m_hitModuleHalfStave(nullptr)
	, m_hitChipModule(nullptr)
	, m_hitLayerMap(nullptr)
	, m_hitPixelPhiMap(nullptr)
	, m_hitPixelPhiMapHL(nullptr)
	  , m_hitPixelZMap(nullptr)
{
	_foutname = filename;
}

TFile * DebugFile;
TTree * HitTreeZZ;


int HitSize;
int EvtID;
int HitX[1000];
int HitY[1000];
int HitZ[1000];
int TrkID[1000];

unsigned int long long NEGED;

int HFMLTriggerInterface::Init(PHCompositeNode* topNode)
{

	_ievent = 0;
	
	DebugFile = new TFile("DebugFile.root","RECREATE");

	DebugFile->cd();

	HitTreeZZ = new TTree("HitTreeZZ","HitTreeZZ");

	HitTreeZZ->Branch("EvtID",&EvtID,"EvtID/I");
	HitTreeZZ->Branch("HitSize",&HitSize,"HitSize/I");
	HitTreeZZ->Branch("HitX",HitX,"HitX[HitSize]/I");
	HitTreeZZ->Branch("HitY",HitY,"HitY[HitSize]/I");
	HitTreeZZ->Branch("HitZ",HitZ,"HitZ[HitSize]/I");
	HitTreeZZ->Branch("TrkID",TrkID,"TrkID[HitSize]/I");


	_f = new TFile((_foutname + string(".root")).c_str(), "RECREATE");

	m_jsonOut.open((_foutname + string(".json")).c_str(), fstream::out);

	m_jsonOut << "{" << endl;
	m_jsonOut << "\"Events\" : [" << endl;

	//  _h2 = new TH2D("h2", "", 100, 0, 100.0, 40, -2, +2);
	//  _h2_b = new TH2D("h2_b", "", 100, 0, 100.0, 40, -2, +2);
	//  _h2_c = new TH2D("h2_c", "", 100, 0, 100.0, 40, -2, +2);
	//  _h2all = new TH2D("h2all", "", 100, 0, 100.0, 40, -2, +2);

	m_hitLayerMap = new TH3F("hitLayerMap", "hitLayerMap", 600, -10, 10, 600, -10, 10, 10, -.5, 9.5);
	m_hitLayerMap->SetTitle("hitLayerMap;x [mm];y [mm];Half Layers");

	m_hitPixelPhiMap = new TH3F("hitPixelPhiMap", "hitPixelPhiMap", 16000, -.5, 16000 - .5, 600, -M_PI, M_PI, 10, -.5, 9.5);
	m_hitPixelPhiMap->SetTitle("hitPixelPhiMap;PixelPhiIndex in layer;phi [rad];Half Layers Index");
	m_hitPixelPhiMapHL = new TH3F("hitPixelPhiMapHL", "hitPixelPhiMapHL", 16000, -.5, 16000 - .5, 600, -M_PI, M_PI, 10, -.5, 9.5);
	m_hitPixelPhiMapHL->SetTitle("hitPixelPhiMap;PixelPhiIndex in half layer;phi [rad];Half Layers Index");
	m_hitPixelZMap = new TH3F("hitPixelZMap", "hitPixelZMap", 16000, -.5, 16000 - .5, 600, 15, 15, 10, -.5, 9.5);
	m_hitPixelZMap->SetTitle("hitPixelZMap;hitPixelZMap;z [cm];Half Layers");

	m_hitStaveLayer = new TH2F("hitStaveLayer", "hitStaveLayer", 100, -.5, 100 - .5, 10, -.5, 9.5);
	m_hitStaveLayer->SetTitle("hitStaveLayer;Stave index;Half Layers");
	m_hitModuleHalfStave = new TH2F("hitModuleHalfStave", "hitModuleHalfStave", 100, -.5, 100 - .5, 10, -.5, 9.5);
	m_hitModuleHalfStave->SetTitle("hitModuleHalfStave;Module index;Half Stave");
	m_hitChipModule = new TH2F("hitChipModule", "hitChipModule", 100, -.5, 100 - .5, 10, -.5, 9.5);
	m_hitChipModule->SetTitle("hitChipModule;Chip;Module");

	return Fun4AllReturnCodes::EVENT_OK;
}

int HFMLTriggerInterface::InitRun(PHCompositeNode* topNode)
{
	m_Geoms =
		findNode::getClass<PHG4CylinderGeomContainer>(topNode, "CYLINDERGEOM_MVTX");
	if (!m_Geoms)
	{
		std::cout << PHWHERE << "ERROR: Can't find node CYLINDERCELLGEOM_MVTX" << std::endl;
		return Fun4AllReturnCodes::ABORTRUN;
	}

	m_Geoms2 =
		findNode::getClass<PHG4CylinderGeomContainer>(topNode, "CYLINDERGEOM_INTT");
	if (!m_Geoms2)
	{
		std::cout << PHWHERE << "ERROR: Can't find node CYLINDERCELLGEOM_INTT" << std::endl;
		return Fun4AllReturnCodes::ABORTRUN;
	}

	m_truthInfo = findNode::getClass<PHG4TruthInfoContainer>(topNode, "G4TruthInfo");
	if (!m_truthInfo)
	{
		std::cout << PHWHERE << "ERROR: Can't find node G4TruthInfo" << std::endl;
		return Fun4AllReturnCodes::ABORTRUN;
	}

	m_Flags = findNode::getClass<PdbParameterMap>(topNode, "HFMLTrigger_HepMCTriggerFlags");
	if (!m_Flags)
	{
		cout << "HFMLTriggerInterface::InitRun - WARNING - missing HFMLTrigger_HepMCTriggerFlags" << endl;
	}

	return Fun4AllReturnCodes::EVENT_OK;
}

int HFMLTriggerInterface::process_event(PHCompositeNode* topNode)
{
	// load nodes
	auto res = load_nodes(topNode);
	if (res != Fun4AllReturnCodes::EVENT_OK)
		return res;

	/*
	   if (!_svtxevalstack)
	   {
	   _svtxevalstack = new SvtxEvalStack(topNode);
	   _svtxevalstack->set_strict(0);
	   _svtxevalstack->set_verbosity(Verbosity() + 1);
	   SvtxTruthEval* trutheval = _svtxevalstack->get_truth_eval();
	   }
	   else
	   {
	   _svtxevalstack->next_event(topNode);
	   }
	   */

	//  SvtxVertexEval* vertexeval = _svtxevalstack->get_vertex_eval();
	//  SvtxTrackEval* trackeval = _svtxevalstack->get_track_eval();
	// SvtxClusterEval* clustereval = _svtxevalstack->get_cluster_eval();
	//SvtxHitEval* hiteval = _svtxevalstack->get_hit_eval();

	assert(m_GenEventMap);

	PHHepMCGenEvent* genevt = m_GenEventMap->get(_embedding_id);
	if (!genevt)
	{
		std::cout << PHWHERE << " - Fatal error - node PHHepMCGenEventMap missing subevent with embedding ID " << _embedding_id;
		std::cout << ". Print PHHepMCGenEventMap:";
		m_GenEventMap->identify();
		return Fun4AllReturnCodes::ABORTEVENT;
	}

	HepMC::GenEvent* theEvent = genevt->getEvent();
	assert(theEvent);
	if (Verbosity())
	{
		cout << "HFMLTriggerInterface::process_event - process HepMC::GenEvent with signal_process_id = "
			<< theEvent->signal_process_id();
		if (theEvent->signal_process_vertex())
		{
			cout << " and signal_process_vertex : ";
			theEvent->signal_process_vertex()->print();
		}
		cout << "  - Event record:" << endl;
		theEvent->print();
	}

	// property tree preparation
	//  using boost::property_tree::ptree;
	//  ptree pt;

	rapidjson::Document d;
	d.SetObject();
	rapidjson::Document::AllocatorType& alloc = d.GetAllocator();

	auto loadCoordinate = [&](double x, double y, double z) {
		//    ptree vertexTree;
		rapidjson::Value vertexTree(rapidjson::kArrayType);

		//    ptree vertexX;
		//    vertexX.put("", x);
		//    vertexTree.push_back(make_pair("", vertexX));

		//    ptree vertexY;
		//    vertexY.put("", y);
		//    vertexTree.push_back(make_pair("", vertexY));

		//    ptree vertexZ;
		//    vertexZ.put("", z);
		//    vertexTree.push_back(make_pair("", vertexZ));

		vertexTree.PushBack(x, alloc).PushBack(y, alloc).PushBack(z, alloc);

		return vertexTree;
	};

	// Create a root
	//  ptree pTree;

	// meta data
	//  ptree metaTree;
	rapidjson::Value metaTree(rapidjson::kObjectType);

	metaTree.AddMember("Description", "These are meta data for this event. Not intended to use in ML algorithm", alloc);
	metaTree.AddMember("EventID", _ievent, alloc);
	metaTree.AddMember("Unit", "cm", alloc);
	metaTree.AddMember("CollisionVertex",
			loadCoordinate(genevt->get_collision_vertex().x(),
				genevt->get_collision_vertex().y(),
				genevt->get_collision_vertex().z()),
			alloc);

	metaTree.AddMember("Layer_Count", _nlayers_maps, alloc);
	metaTree.AddMember("PixelHalfLayerIndex_Count", _nlayers_maps * 2, alloc);

	for (unsigned int layer = 0; layer < _nlayers_maps; ++layer)
	{
		CylinderGeom_Mvtx* geom = dynamic_cast<CylinderGeom_Mvtx*>(m_Geoms->GetLayerGeom(layer));
		assert(geom);

		//    ptree layerDescTree;
		rapidjson::Value layerDescTree(rapidjson::kObjectType);

		static const unsigned int nChip(9);

		layerDescTree.AddMember("PixelPhiIndexInLayer_Count", geom->get_N_staves() * geom->get_NX(), alloc);
		layerDescTree.AddMember("PixelPhiIndexInHalfLayer_Count", geom->get_N_staves() * geom->get_NX() / 2, alloc);
		layerDescTree.AddMember("PixelZIndex_Count", nChip * geom->get_NZ(), alloc);
		layerDescTree.AddMember("HalfLayer_Count", 2, alloc);
		layerDescTree.AddMember("Stave_Count", geom->get_N_staves(), alloc);
		layerDescTree.AddMember("Chip_Count", nChip, alloc);
		layerDescTree.AddMember("Pixel_Count", geom->get_NX() * geom->get_NZ(), alloc);

		//    metaTree.AddMember(
		//        str(boost::format{"Layer%1%"} % layer).c_str(),
		//        layerDescTree, alloc);
		rapidjson::Value keyName(str(boost::format{"Layer%1%"} % layer).c_str(), alloc);
		metaTree.AddMember(keyName,
				layerDescTree, alloc);
	}

	//  ptree truthTriggerFlagTree;
	rapidjson::Value truthTriggerFlagTree(rapidjson::kObjectType);

	truthTriggerFlagTree.AddMember("Description",
			"These are categorical true/false MonteCalo truth tags for the event. These are only known in training sample. This would be trigger output in real data processing.",
			alloc);
	//    truthTriggerFlagTree.AddMember("ExampleSignal1", true, alloc);
	//    truthTriggerFlagTree.AddMember("ExampleSignal2", false, alloc);
	rapidjson::Value flagsTree(rapidjson::kObjectType);
	if (m_Flags)
	{
		auto range = m_Flags->get_iparam_iters();

		for (auto flagIter = range.first; flagIter != range.second; ++flagIter)
		{
			//      rapidjson::Value aFlag(rapidjson::kObjectType);

			const string& name = flagIter->first;
			rapidjson::Value keyName(name.c_str(), alloc);
			const bool flag = flagIter->second > 0 ? true : false;

			flagsTree.AddMember(keyName, flag, alloc);
			//      flagsTree.PushBack(aFlag, alloc);
		}
	}
	truthTriggerFlagTree.AddMember("Flags", flagsTree, alloc);

	// Raw hits
	//  ptree rawHitTree;
	rapidjson::Value rawHitTree(rapidjson::kObjectType);
	rawHitTree.AddMember("Description",
			"Raw data in the event in an unordered set of hit ID. To help in visualization stage, the coordinate of the hit is also appended. These would be input in real data.",
			alloc);

	//  rawHitTree.put("LayerRage", "0-2");

	//  ptree rawHitsTree;
	rapidjson::Value rawHitsTree(rapidjson::kArrayType);



	assert(m_hitsets);
	unsigned int hitID(0);
	//	vector<vector<int>> HitInfo;
	//	vector<vector<int>> HitInfo_INTT;
	vector<int> TrkIDVec;
	vector<int> HitIDVec;
	vector<uint64_t> KeyIDVec;

	HitSize = 0;

	//int IndexID;

	NEGED = 0;

	auto hitset_range = m_hitsets->getHitSets(TrkrDefs::TrkrId::mvtxId);
	for (auto hitset_iter =  hitset_range.first; hitset_iter != hitset_range.second; ++hitset_iter)
	{
		auto hitsetkey = hitset_iter->first;
		auto hit_range = hitset_iter->second->getHits();
		for (auto hit_iter = hit_range.first;
				hit_iter != hit_range.second;
				++hit_iter)
		{
			auto hitkey = hit_iter->first;
			auto hit = hit_iter->second;
			assert(hit);
			// get truth hit assoc
			int trkid;
			TrkrHitTruthAssoc::MMap g4hit_map;
			m_hit_truth_map->getG4Hits(hitsetkey, hitkey, g4hit_map);
		//	int SUCK = 0;
			if (g4hit_map.size() != 1)
			{
				std::cout << "More than one (" << g4hit_map.size() <<") g4Hit associated to " << hitkey << std::endl;
	//			SUCK = 1;
			}
			rapidjson::Value truthHitTree(rapidjson::kArrayType);
			for (auto truth_iter = g4hit_map.begin(); truth_iter != g4hit_map.end(); ++truth_iter)
			{
				// g4hit key
				const auto g4hit_key = truth_iter->second.second;
				truthHitTree.PushBack(static_cast<uint64_t>(g4hit_key), alloc);
			

				//cout << "static_cast<uint64_t>(g4hit_key) = " << static_cast<uint32_t>(g4hit_key) << "    static_cast<uint64_t>(g4hit_key) = " << static_cast<uint64_t>(g4hit_key) << endl;
				

				PHG4Hit *g4hit = m_g4hits_mvtx->findHit( static_cast<uint64_t>(g4hit_key) );

				trkid =  g4hit->get_trkid();

			//	if(trkid < 0) cout << "trkid = " << trkid << "   static_cast<uint64_t>(g4hit_key) =  " <<  static_cast<uint64_t>(g4hit_key) << endl;
			//	if(SUCK == 1) cout << "trkid = " << trkid << "   static_cast<uint64_t>(g4hit_key) =  " <<  static_cast<uint64_t>(g4hit_key) << endl;
				if(trkid < 0 ) NEGED = static_cast<uint64_t>(g4hit_key);

				//	auto hitid =  g4hit->get_hit_id();
				HitIDVec.push_back(hitID);
				TrkIDVec.push_back(trkid);

				KeyIDVec.push_back(static_cast<uint64_t>(g4hit_key));

				//cout << "MVTX: trkid =  " << trkid << "  hitID =  " << hitID<< endl;



				//cout << "trkid =  " << trkid << "  hitid =  " << hitid<< endl;


			}

			unsigned int layer = TrkrDefs::getLayer(hitset_iter->first);
			if (layer < _nlayers_maps)
			{
				CylinderGeom_Mvtx* geom = dynamic_cast<CylinderGeom_Mvtx*>(m_Geoms->GetLayerGeom(layer));
				assert(geom);

				unsigned int pixel_x = MvtxDefs::getRow(hitkey);
				unsigned int pixel_z = MvtxDefs::getCol(hitkey);
				assert((int)pixel_x < geom->get_NX());
				assert((int)pixel_z < geom->get_NZ());
				unsigned int chip = MvtxDefs::getChipId(hitsetkey);
				unsigned int stave = MvtxDefs::getStaveId(hitsetkey);
				TVector3 local_coords = geom->get_local_coords_from_pixel(pixel_x, pixel_z);
				TVector3 world_coords = geom->get_world_from_local_coords(stave,
						0,
						0,
						chip,
						local_coords);

				//unsigned int halflayer = (int) pixel_x >= geom->get_NX() / 2 ? 0 : 1;

				//unsigned int halfLayerIndex(layer * 2 + halflayer);
				//unsigned int pixelPhiIndex(
				//  cell->get_stave_index() * geom->get_NX() + pixel_x);
				//unsigned int pixelPhiIndexHL(
				//  cell->get_stave_index() * geom->get_NX() / 2 + pixel_x % (geom->get_NX() / 2));
				// unsigned int pixelZIndex(cell->get_chip_index() * geom->get_NZ() + pixel_z);

				//      ptree hitTree;
				rapidjson::Value hitTree(rapidjson::kObjectType);

				//      ptree hitIDTree;
				rapidjson::Value hitIDTree(rapidjson::kObjectType);
				hitIDTree.AddMember("HitSequenceInEvent", hitID, alloc);
				hitIDTree.AddMember("G4HitAssoc", truthHitTree, alloc);
				hitIDTree.AddMember("MVTXTrkID", trkid, alloc);

				//hitIDTree.AddMember("PixelHalfLayerIndex", halfLayerIndex, alloc);
				//hitIDTree.AddMember("PixelPhiIndexInLayer", pixelPhiIndex, alloc);
				//hitIDTree.AddMember("PixelPhiIndexInHalfLayer", pixelPhiIndexHL, alloc);
				//hitIDTree.AddMember("PixelZIndex", pixelZIndex, alloc);

				hitIDTree.AddMember("Layer", layer, alloc);
				//hitIDTree.AddMember("HalfLayer", halflayer, alloc);
				hitIDTree.AddMember("Stave", stave, alloc);
				//      hitIDTree.put("HalfStave", cell->get_half_stave_index());
				//      hitIDTree.put("Module", cell->get_module_index());
				hitIDTree.AddMember("Chip", chip, alloc);
				hitIDTree.AddMember("Pixel_x", pixel_x, alloc);
				hitIDTree.AddMember("Pixel_z", pixel_z, alloc);
				hitTree.AddMember("ID", hitIDTree, alloc);

				hitTree.AddMember("Coordinate",
						loadCoordinate(world_coords.x(),
							world_coords.y(),
							world_coords.z()),
						alloc);

				//      rawHitsTree.add_child("MVTXHit", hitTree);
				rawHitsTree.PushBack(hitTree, alloc);

				m_hitStaveLayer->Fill(stave, layer);
				m_hitModuleHalfStave->Fill(stave, layer);
				m_hitChipModule->Fill(chip, stave);

				m_hitLayerMap->Fill(world_coords.x(), world_coords.y(), layer);
				//m_hitPixelPhiMap->Fill(pixelPhiIndex, atan2(world_coords.y(), world_coords.x()), layer);
				//m_hitPixelPhiMapHL->Fill(pixelPhiIndexHL, atan2(world_coords.y(), world_coords.x()), layer);
				//m_hitPixelZMap->Fill(pixelZIndex, world_coords.z(), halfLayerIndex);

				HitX[HitSize] = world_coords.x();
				HitY[HitSize] = world_coords.y();
				HitZ[HitSize] = world_coords.z();
				TrkID[HitSize] = trkid;
				
				++hitID;
				HitSize = HitSize + 1;
			}  //    if (layer < _nlayers_maps)
		}  //   for (TrkrHitSetContainer::ConstIterator hitset_iter = hitset_range.first;
	}  //   for (TrkrHitSet::ConstIterator hit_iter = hit_range.first;
	rawHitTree.AddMember("MVTXHits", rawHitsTree, alloc);


	rapidjson::Value rawHitsTree2(rapidjson::kArrayType);


	TrkrHitSetContainer::ConstRange hitset_range_intt = m_hitsets->getHitSets(TrkrDefs::TrkrId::inttId);

	int INTTHITS = 0;
	unsigned int hitIDINTT(0);

	vector<int> TrkIDVecINTT;
	vector<int> HitIDVecINTT;
	vector<uint64_t> KeyIDVecINTT;


	for (TrkrHitSetContainer::ConstIterator hitset_iter = hitset_range_intt.first;
			hitset_iter != hitset_range_intt.second;
			++hitset_iter)
	{
		//	  TrkrDefs::hitsetkey hitSetKey = hitset_iter->first;
		auto hitsetkey = hitset_iter->first;

		TrkrHitSet::ConstRange hit_range = hitset_iter->second->getHits();
		for (TrkrHitSet::ConstIterator hit_iter = hit_range.first;
				hit_iter != hit_range.second;
				++hit_iter)
		{

			//		cout << "Pass 1" << endl;
			TrkrDefs::hitkey hitKey = hit_iter->first;
			TrkrHit* hit = hit_iter->second;
			assert(hit);
			unsigned int layer = TrkrDefs::getLayer(hitset_iter->first);
			//	cout << "Pass 2" << "   layer = " << layer  << endl;


			int trkid;		
			// get truth hit assoc
			TrkrHitTruthAssoc::MMap g4hit_map;
			m_hit_truth_map->getG4Hits(hitsetkey, hitKey, g4hit_map);
			if (g4hit_map.size() != 1)
			{
				std::cout << "More than one (" << g4hit_map.size() <<") g4Hit associated to " << hitKey << std::endl;
			}
			rapidjson::Value truthHitTree(rapidjson::kArrayType);
			for (auto truth_iter = g4hit_map.begin(); truth_iter != g4hit_map.end(); ++truth_iter)
			{
				// g4hit key
				const auto g4hit_key = truth_iter->second.second;
				truthHitTree.PushBack(static_cast<uint64_t>(g4hit_key), alloc);

				PHG4Hit *g4hit = m_g4hits_intt->findHit( static_cast<uint64_t>(g4hit_key) );

				trkid =  g4hit->get_trkid();
				HitIDVecINTT.push_back(hitIDINTT);	
				TrkIDVecINTT.push_back(trkid);
				KeyIDVecINTT.push_back(static_cast<uint64_t>(g4hit_key) );

				//	auto hitid =  g4hit->get_hit_id();

				//	HitInfo_INTT[trkid].push_back(hitIDINTT);
				//cout << "INTT:: trkid =  " << trkid << endl;

				//	cout << "INTT: trkid =  " << trkid << "  hitIDINTT =  " << hitIDINTT << endl;

			}


			if(layer > _nlayers_maps-1){

				CylinderGeomIntt* geom = dynamic_cast<CylinderGeomIntt*>(m_Geoms2->GetLayerGeom(layer));
				//		cout << "Pass 3" << endl;


				unsigned int Row = InttDefs::getRow(hitKey);
				unsigned int Col = InttDefs::getCol(hitKey);
				unsigned int LadderZId = InttDefs::getLadderZId(hitKey);
				unsigned int LadderPhiId = InttDefs::getLadderPhiId(hitKey);





				double hit_location[3] = {0.0, 0.0, 0.0};

				geom->find_strip_center(LadderZId,
						LadderPhiId,
						Col,
						Row,
						hit_location);


				rapidjson::Value hitTree2(rapidjson::kObjectType);

				rapidjson::Value hitIDTree2(rapidjson::kObjectType);

				//int inttlayer = layer - _nlayers_maps;
				hitIDTree2.AddMember("HitSequenceInEvent", hitIDINTT, alloc);
				hitIDTree2.AddMember("G4HitAssoc", truthHitTree, alloc);	
				hitIDTree2.AddMember("INTTTrkID", trkid, alloc);

				hitIDTree2.AddMember("Layer", layer, alloc);
				hitIDTree2.AddMember("Row", Row, alloc);
				hitIDTree2.AddMember("Col", Col, alloc);
				hitIDTree2.AddMember("LadderZId", LadderZId, alloc);
				hitIDTree2.AddMember("LadderPhiId", LadderPhiId, alloc);

				hitTree2.AddMember("ID", hitIDTree2, alloc);

				/*
				   cout << "layer = " << layer << endl;
				   cout << "Pixel_x = " << pixel_x << endl;
				   cout << "Pixel_z = " << pixel_z << endl;
				   cout << "LadderZId = " << LadderZId << endl;
				   cout << "LadderPhiId = " << LadderPhiId << endl;
				   */

				hitTree2.AddMember("Coordinate",	loadCoordinate(hit_location[0], hit_location[1], hit_location[2]),	alloc);

				//cout << "Pass 4" << endl;
				rawHitsTree2.PushBack(hitTree2, alloc);


				//		rawHitTree.PushBack(hitTree2, alloc);

				m_hitLayerMap->Fill(hit_location[0], hit_location[1], layer);

				HitX[HitSize] = hit_location[0];
				HitY[HitSize] = hit_location[1];
				HitZ[HitSize] = hit_location[2];
				TrkID[HitSize] = trkid;


				hitIDINTT++;
				HitSize = HitSize + 1;
				
			}

			//	cout << "Pass 5" << endl;

		}

		INTTHITS = INTTHITS + 1;

	}

	rawHitTree.AddMember("INTTHITS", rawHitsTree2, alloc);

	//	cout << "Pass 6" << endl;

	//	cout << "ZZ Check: INTTHITS = " << INTTHITS << endl;




	vector<int> IndexVec;
	vector<int> IndexVecINTT;


	// Truth hits
	//  ptree truthHitTree;
	rapidjson::Value truthHitTree(rapidjson::kObjectType);
	truthHitTree.AddMember("Description", "From the MonteCalo truth information, pairs of track ID and subset of RawHit that belong to the track. These are not presented in real data. The track ID is arbitary.",
			alloc);

	//MVTX

	assert(m_g4hits_mvtx);
	std::multimap<const int, const unsigned long long> m_track_g4hits_map;
	for (auto g4hit_iter = m_g4hits_mvtx->getHits().first;
			g4hit_iter != m_g4hits_mvtx->getHits().second;
			++g4hit_iter)
	{
		PHG4Hit *g4hit = g4hit_iter->second;

	//	if(g4hit->get_hit_id() == NEGED) cout << "g4hit->get_hitid() = " << g4hit->get_hit_id() << "      g4hit->get_trkid()  = " << g4hit->get_trkid() << endl;

		int trkidCheck  = g4hit->get_trkid();
		
		PHG4Particle * ParticleDebug =  m_truthInfo->GetParticle(trkidCheck);

		cout << "g4hit->get_hitid() = " << g4hit->get_hit_id() << "      g4hit->get_trkid()  = " << g4hit->get_trkid() << "   ParticleDebug->get_pid() =  " << ParticleDebug->get_pid() << endl;
		
		m_track_g4hits_map.insert(make_pair(g4hit->get_trkid(), g4hit_iter->first));
	}


	//INTT


	assert(m_g4hits_intt);
	std::multimap<const int, const unsigned long long> m_track_g4hits_map_intt;
	for (auto g4hit_iter = m_g4hits_intt->getHits().first;
			g4hit_iter != m_g4hits_intt->getHits().second;
			++g4hit_iter)
	{
		PHG4Hit *g4hit = g4hit_iter->second;
		m_track_g4hits_map_intt.insert(make_pair(g4hit->get_trkid(), g4hit_iter->first));
	}


	//  ptree truthTracksTree;
	rapidjson::Value truthTracksTree(rapidjson::kArrayType);
	// get set of primary particle
	assert(m_truthInfo);
	auto pp_range = m_truthInfo->GetPrimaryParticleRange();
	for (auto pp_iter = pp_range.first;
			pp_iter != pp_range.second;
			++pp_iter)
	{

		PHG4Particle *g4particle = pp_iter->second;
		assert(g4particle);
		//  vtx = trutheval->get_vertex(g4particle);

		vtx = m_truthInfo->GetVtx(g4particle->get_vtx_id());

		if (! m_track_g4hits_map.count(g4particle->get_track_id()))
		{
			if (Verbosity() >= VERBOSITY_MORE)
				std::cout << "WARNING: G4 particle " << g4particle->get_track_id() \
					<< " does not hit any MVTX layer." << std::endl;
			continue;
		}
		if (! m_track_g4hits_map_intt.count(g4particle->get_track_id()))
		{
			if (Verbosity() >= VERBOSITY_MORE)
				std::cout << "WARNING: G4 particle " << g4particle->get_track_id() \
					<< " does not hit any INTT layer." << std::endl;
			continue;
		}


		//    ptree trackHitTree;
		//rapidjson::Document trackHitTree;

		rapidjson::Value trackHitTree(rapidjson::kArrayType);



		rapidjson::Value MVTXHitIDTree(rapidjson::kArrayType);
		rapidjson::Value MVTXHitIDTree2(rapidjson::kArrayType);


		int trkid = g4particle->get_track_id();

		//MVTX
		int LayerHere = 0;
		auto g4hits_iter = m_track_g4hits_map.equal_range(g4particle->get_track_id());
		 
		//if(g4particle->get_track_id() < 0)	cout << "g4particle->get_track_id() = " << g4particle->get_track_id() << endl;
		cout << "g4particle->get_track_id() = " << g4particle->get_track_id() << endl;

		for (auto& g4hit_iter = g4hits_iter.first;
				g4hit_iter != g4hits_iter.second; ++g4hit_iter)
		{
			//          ptree hitIDTree;
			//          hitIDTree.put("", g4hit_key);
			//	int Info[2];
			//	HitInFoVec.first = LayerHere;
			//	HitInFoVec.second =  static_cast<uint64_t>(g4hit_iter->second);

			


			//	cout << "HitInfo[trkid].size() = " << HitInfo[trkid].size() << endl;

			rapidjson::Value trackHitTree2(rapidjson::kArrayType);

			trackHitTree2.PushBack(LayerHere, alloc);
			trackHitTree2.PushBack(static_cast<uint64_t>(g4hit_iter->second), alloc);
			
/*
			PHG4Hit *g4hit = m_g4hits_mvtx->findHit( static_cast<uint64_t>(g4hit_iter->second) );
			if(g4hit->get_trkid() < 0){
				cout << "g4hit->get_hitid() = " << g4hit->get_hit_id() << "      g4hit->get_trkid()  = " << g4hit->get_trkid() << "  g4particle->get_track_id() = " << g4particle->get_track_id() << "   g4particle->get_pid() = " <<  g4particle->get_pid() << endl;


			}
*/
			trackHitTree.PushBack(trackHitTree2, alloc);

			//    rapidjson::Value LayerID(LayerHere, alloc);
			//    rapidjson::Value TruthHitKey(static_cast<uint64_t>(g4hit_iter->second), alloc);
			//	trackHitTree.AddMember(LayerID,TruthHitKey, alloc);
			LayerHere = LayerHere + 1;


			IndexVec.clear();

			int KeyIDVecSize = KeyIDVec.size();

			for(int i = 0; i < KeyIDVecSize; i++){


				if(static_cast<uint64_t>(g4hit_iter->second) == KeyIDVec[i]) IndexVec.push_back(i);

			}
			int	HitSize = IndexVec.size();
			//		cout << "HitSize = " << HitSize << endl;

			for(int i = 0; i < HitSize; i++){

				int IndexID = IndexVec[i];

				MVTXHitIDTree2.PushBack(HitIDVec[IndexID],alloc);


			}





		}  //   for (auto& clus_key : clus_keys)





		MVTXHitIDTree.PushBack(MVTXHitIDTree2, alloc);














		//INTT
		//		cout << "Pass 6.6" << endl;


		rapidjson::Value INTTHitIDTree(rapidjson::kArrayType);
		rapidjson::Value INTTHitIDTree2(rapidjson::kArrayType);

		//		cout << "Pass 6.7" << endl;

		auto g4hits_iter_intt = m_track_g4hits_map_intt.equal_range(g4particle->get_track_id());

		







		LayerHere = 3;

		for (auto& g4hit_iter = g4hits_iter_intt.first;
				g4hit_iter != g4hits_iter_intt.second; ++g4hit_iter)
		{
			//          ptree hitIDTree;
			//          hitIDTree.put("", g4hit_key);
			//	int Info[2];
			//	HitInFoVec.first = LayerHere;
			//	HitInFoVec.second =  static_cast<uint64_t>(g4hit_iter->second);




			//	cout << "HitInfo[trkid].size() = " << HitInfo[trkid].size() << endl;

			rapidjson::Value trackHitTree2(rapidjson::kArrayType);

			trackHitTree2.PushBack(LayerHere, alloc);
			trackHitTree2.PushBack(static_cast<uint64_t>(g4hit_iter->second), alloc);

			trackHitTree.PushBack(trackHitTree2, alloc);

			//    rapidjson::Value LayerID(LayerHere, alloc);
			//    rapidjson::Value TruthHitKey(static_cast<uint64_t>(g4hit_iter->second), alloc);
			//	trackHitTree.AddMember(LayerID,TruthHitKey, alloc);
			LayerHere = LayerHere + 1;


			IndexVecINTT.clear();




			//	cout << "Pass 6.10" << endl;


			int KeyIDVecSize_intt = KeyIDVecINTT.size();




 			

			//	cout << "Pass 6.11" << endl;

			for(int i = 0; i < KeyIDVecSize_intt; i++){


				if(static_cast<uint64_t>(g4hit_iter->second) == KeyIDVecINTT[i]) IndexVecINTT.push_back(i);

			}

			//	cout << "Pass 6.12" << endl;

			int	HitSize_intt = IndexVecINTT.size();

			//		cout << "HitSize_intt = " << HitSize_intt << endl;

			for(int i = 0; i < HitSize_intt; i++){

				int IndexID = IndexVecINTT[i];


				INTTHitIDTree2.PushBack(HitIDVecINTT[IndexID],alloc);

			}





		}  //   for (auto& clus_key : clus_keys)





		INTTHitIDTree.PushBack(INTTHitIDTree2, alloc);












		//      ptree trackTree;
		rapidjson::Value trackTree(rapidjson::kObjectType);
		trackTree.AddMember("OriginVertexPoint", loadCoordinate(vtx->get_x(),vtx->get_y(),vtx->get_z()), alloc);
		trackTree.AddMember("TrackSequenceInEvent", g4particle->get_track_id(), alloc);
		trackTree.AddMember("HitInTruthTrack", trackHitTree, alloc);
		trackTree.AddMember("TrackID", trkid, alloc);		
		trackTree.AddMember("MVTXHitID", MVTXHitIDTree, alloc);
		trackTree.AddMember("INTTHitID", INTTHitIDTree, alloc);

		trackTree.AddMember("ParticleTypeID", g4particle->get_pid(), alloc);
		trackTree.AddMember("TrackMomentum",
				loadCoordinate(g4particle->get_px(),
					g4particle->get_py(),
					g4particle->get_pz()),
				alloc);
		trackTree.AddMember("TrackEnergy",g4particle->get_e() , alloc);

		//      trackTree.put("TrackDCA3DXY", track->get_dca3d_xy());
		//      trackTree.put("TrackDCA3DZ", track->get_dca3d_z());

		//      trackTree.add_child("TruthHit", trackHitTree);

		//      truthTracksTree.add_child("TruthTrack", trackTree);
		truthTracksTree.PushBack(trackTree, alloc);



		//cout << "g4particle->get_pid() = " << g4particle->get_pid() << "   g4particle->get_Z() = " << g4particle->get_Z()  << endl;
	}  //  for (PHG4TruthInfoContainer::ConstIterator iter = range.first;

	truthHitTree.AddMember("TruthTracks", truthTracksTree, alloc);

	//output
	d.AddMember("MetaData", metaTree, alloc);
	d.AddMember("TruthTriggerFlag", truthTriggerFlagTree, alloc);
	d.AddMember("RawHit", rawHitTree, alloc);
	d.AddMember("TruthHit", truthHitTree, alloc);

	assert(m_jsonOut.is_open());

	if (_ievent > 0)
	{
		m_jsonOut << "," << endl;
	}

	//  write_json(m_jsonOut, pTree);
	//  write_xml(m_jsonOut, jsonTree);

	//  d.AddMember("Test", 1, d.GetAllocator());

	rapidjson::OStreamWrapper osw(m_jsonOut);
	rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(osw);

	d.Accept(writer);

	
	EvtID = _ievent;
	HitTreeZZ->Fill();

	++_ievent;
	
	return Fun4AllReturnCodes::EVENT_OK;
}

int HFMLTriggerInterface::End(PHCompositeNode* topNode)
{
	if (_f)
	{
		_f->cd();
		_f->Write();
	}

	DebugFile->cd();
	DebugFile->Write();

	if (m_jsonOut.is_open())
	{
		m_jsonOut << "]" << endl;
		m_jsonOut << "}" << endl;

		m_jsonOut.close();
	}

	cout << "HFMLTriggerInterface::End - output to " << _foutname << ".*" << endl;

	return Fun4AllReturnCodes::EVENT_OK;
}

int HFMLTriggerInterface::load_nodes(PHCompositeNode* topNode)
{

	m_hitsets = findNode::getClass<TrkrHitSetContainer>(topNode, "TRKR_HITSET");
	if (!m_hitsets)
	{
		std::cout << PHWHERE << "ERROR: Can't find node TRKR_HITSET" << std::endl;
		return Fun4AllReturnCodes::ABORTEVENT;
	}

	m_hit_truth_map = findNode::getClass<TrkrHitTruthAssoc>(topNode, "TRKR_HITTRUTHASSOC");
	if (!m_hit_truth_map)
	{
		std::cout << PHWHERE << " unable to find DST node TRKR_HITTRUTHASSOC" << std::endl;
		return Fun4AllReturnCodes::ABORTEVENT;
	}

	//m_cluster_hit_map = findNode::getClass<TrkrClusterHitAssoc>(topNode, "TRKR_CLUSTERHITASSOC");
	//if (!m_cluster_hit_map)
	//{
	//  std::cout << PHWHERE << " unable to find DST node TRKR_CLUSTERHITASSOC" << std::endl;
	//  return Fun4AllReturnCodes::ABORTEVENT;
	//}

	m_g4hits_mvtx = findNode::getClass<PHG4HitContainer>(topNode, "G4HIT_MVTX");
	if (!m_g4hits_mvtx)
	{
		std::cout << PHWHERE << " unable to find DST node G4HIT_MVTX" << std::endl;
		return Fun4AllReturnCodes::ABORTEVENT;
	}


	m_g4hits_intt = findNode::getClass<PHG4HitContainer>(topNode, "G4HIT_INTT");
	if (!m_g4hits_intt)
	{
		std::cout << PHWHERE << " unable to find DST node G4HIT_INTT" << std::endl;
		return Fun4AllReturnCodes::ABORTEVENT;
	}


	m_GenEventMap = findNode::getClass<PHHepMCGenEventMap>(topNode, "PHHepMCGenEventMap");
	if (!m_GenEventMap)
	{
		std::cout << PHWHERE << " - Fatal error - missing node PHHepMCGenEventMap" << std::endl;
		return Fun4AllReturnCodes::ABORTEVENT;
	}

	return Fun4AllReturnCodes::EVENT_OK;
}
