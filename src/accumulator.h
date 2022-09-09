//
// Copyright (c) 2017-2022, Manticore Software LTD (https://manticoresearch.com)
// All rights reserved
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License. You should have
// received a copy of the GPL license along with this program; if you
// did not, you can find it at http://www.gnu.org/
//

/// @file _accumulator.h_
/// Declarations for the stuff related to accumulator


#ifndef _accumulator_
#define _accumulator_

#include "sphinxint.h"

struct StoredQueryDesc_t
{
	CSphFixedVector<CSphFilterSettings>	m_dFilters { 0 };
	CSphFixedVector<FilterTreeItem_t>	m_dFilterTree { 0 };

	CSphString						m_sQuery;
	CSphString						m_sTags;
	int64_t							m_iQUID = 0;
	bool							m_bQL = true;
};

class StoredQuery_i : public ISphNoncopyable, public StoredQueryDesc_t
{
public:
	virtual ~StoredQuery_i() {}
};

// commands that got replicated, transactions
enum class ReplicationCommand_e
{
	PQUERY_ADD = 0,
	PQUERY_DELETE,
	TRUNCATE,
	CLUSTER_ALTER_ADD,
	CLUSTER_ALTER_DROP,
	RT_TRX,
	UPDATE_API,
	UPDATE_QL,
	UPDATE_JSON,

	TOTAL
};

// command trait
struct ReplicationCommand_t
{
	// common
	ReplicationCommand_e	m_eCommand { ReplicationCommand_e::TOTAL };
	CSphString				m_sIndex; // move to accumulator
	CSphString				m_sCluster;

	// add
	std::unique_ptr<StoredQuery_i> m_pStored;

	// delete
	CSphVector<int64_t>		m_dDeleteQueries;
	CSphString				m_sDeleteTags;

	// truncate
	std::unique_ptr<CSphReconfigureSettings> m_tReconfigure;

	// commit related
	bool					m_bCheckIndex = true;
	bool					m_bIsolated = false;

	// update
	AttrUpdateSharedPtr_t m_pUpdateAPI;
	bool m_bBlobUpdate = false;
	const CSphQuery * m_pUpdateCond = nullptr;
};

std::unique_ptr<ReplicationCommand_t> MakeReplicationCommand ( ReplicationCommand_e eCommand, CSphString sIndex, CSphString sCluster = CSphString() );

class RtIndex_i;
class ColumnarBuilderRT_i;

/// indexing accumulator
class RtAccum_t
{
public:
	DWORD							m_uAccumDocs {0};
	CSphTightVector<CSphWordHit>	m_dAccum;
	CSphTightVector<CSphRowitem>	m_dAccumRows;
	CSphVector<DocID_t>				m_dAccumKlist;
	CSphTightVector<BYTE>			m_dBlobs;
	CSphVector<DWORD>				m_dPerDocHitsCount;
	CSphVector<std::unique_ptr<ReplicationCommand_t>> m_dCmd;

	bool						m_bKeywordDict {true};
	DictRefPtr_c				m_pDict;
	const void *				m_pRefDict = nullptr; // not owned, used only for comparing via ==


					explicit RtAccum_t ( bool bKeywordDict );
					~RtAccum_t() = default;

	void			SetupDict ( const RtIndex_i * pIndex, const DictRefPtr_c& pDict, bool bKeywordDict );
	void			Sort();

	void			CleanupPart();
	void			Cleanup();

	void			AddDocument ( ISphHits * pHits, const InsertDocData_t & tDoc, bool bReplace, int iRowSize, const DocstoreBuilder_i::Doc_t * pStoredDoc );
	RtSegment_t *	CreateSegment ( int iRowSize, int iWordsCheckpoint, ESphHitless eHitless, const VecTraits_T<SphWordID_t> & dHitlessWords );
	void			CleanupDuplicates ( int iRowSize );
	void			GrabLastWarning ( CSphString & sWarning );
	void			SetIndex ( RtIndex_i * pIndex );

	RowID_t			GenerateRowID();
	void			ResetRowID();
	uint64_t		GetSchemaHash() const { return m_uSchemaHash; }

	RtIndex_i *		GetIndex() const { return m_pIndex; }
	ReplicationCommand_t * AddCommand ( ReplicationCommand_e eCmd, CSphString sIndex, CSphString sCluster = CSphString() );

	void			LoadRtTrx ( const BYTE * pData, int iLen );
	void			SaveRtTrx ( MemoryWriter_c & tWriter ) const;

	const BYTE *	GetPackedKeywords() const;
	int				GetPackedLen() const;

	bool			SetupDocstore ( const RtIndex_i & tIndex, CSphString & sError );

private:
	bool								m_bReplace = false;		///< insert or replace mode (affects CleanupDuplicates() behavior)

	ISphRtDictWraperRefPtr_c			m_pDictRt;
	std::unique_ptr<BlobRowBuilder_i>	m_pBlobWriter;
	std::unique_ptr<DocstoreRT_i>		m_pDocstore {nullptr};
	std::unique_ptr<ColumnarBuilderRT_i>	m_pColumnarBuilder {nullptr};
	RowID_t								m_tNextRowID = 0;
	CSphFixedVector<BYTE>				m_dPackedKeywords { 0 };
	uint64_t							m_uSchemaHash = 0;

	// FIXME!!! index is unlocked between add data and commit or at begin and end
	RtIndex_i *							m_pIndex = nullptr;		///< my current owner in this thread

	void			ResetDict();
	void			SetupDocstore();
	void			CreateSegmentHits ( RtSegment_t * pSeg, int iWordsCheckpoint, ESphHitless eHitless, const VecTraits_T<SphWordID_t> & dHitlessWords );
};

#endif // _accumulator_
