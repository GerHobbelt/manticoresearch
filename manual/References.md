# References

### SQL commands
##### Schema management
* [CREATE TABLE](Creating_a_table/Local_tables/Plain_and_real-time_table_settings.md#General-syntax-of-CREATE-TABLE) - Creates new table
* [CREATE TABLE LIKE](Creating_a_table/Local_tables/Plain_and_real-time_table_settings.md#General-syntax-of-CREATE-TABLE) - Creates table using another one as a template
* [DESCRIBE](Listing_tables.md#DESCRIBE) - Prints out table's field list and their types
* [ALTER TABLE](Updating_table_schema_and_settings.md) - Changes table schema / settings
* [ALTER TABLE REBUILD SECONDARY](Updating_table_schema_and_settings.md#Rebuild-secondary-index) - Updates/recovers secondary indexes
* [DROP TABLE IF EXISTS](Deleting_a_table.md#Deleting-a-table) - Deletes a table (if it exists)
* [SHOW TABLES](Listing_tables.md#DESCRIBE) - Shows tables list
* [SHOW CREATE TABLE](Listing_tables.md#DESCRIBE) - Shows SQL command how to create the table
* [SHOW TABLE STATUS](Node_info_and_management/Table_settings_and_status/SHOW_TABLE_STATUS.md) - Shows information about current table status
* [SHOW TABLE SETTINGS](Node_info_and_management/Table_settings_and_status/SHOW_TABLE_SETTINGS.md) - Shows table settings

##### Data management
* [INSERT](Data_creation_and_modification/Adding_documents_to_a_table/Adding_documents_to_a_real-time_table.md) - Adds new documents
* [REPLACE](Data_creation_and_modification/Updating_documents/REPLACE.md) - Replaces existing documents with new ones
* [UPDATE](Data_creation_and_modification/Updating_documents/UPDATE.md) - Does in-place update in documents
* [DELETE](Data_creation_and_modification/Deleting_documents.md) - Deletes documents
* [TRUNCATE TABLE](Emptying_a_table.md) - Deletes all documents from table

##### Backup
* [BACKUP](Securing_and_compacting_a_table/Backup_and_restore.md#BACKUP-SQL-command-reference) - Backs up your tables

##### SELECT
* [SELECT](Searching/Full_text_matching/Basic_usage.md#SQL) - Searches
  * [WHERE](Searching/Filters.md#Filters) - Filters
  * [GROUP BY](Searching/Grouping.md) - Groups search results
  * [GROUP BY ORDER](Searching/Grouping.md) - Orders groups
  * [GROUP BY HAVING](Searching/Grouping.md) - Filters groups
  * [OPTION](Searching/Options.md#OPTION) - Query Options
  * [FACET](Searching/Faceted_search.md) - Faceted search
  * [SUB-SELECTS](Searching/Sub-selects.md) - About using SELECT sub-queries
* [EXPLAIN QUERY](Searching/Full_text_matching/Profiling.md#Profiling-without-running-a-query) - Shows query execution plan without running the query itself
* [SHOW META](Node_info_and_management/SHOW_META.md) - Shows extended information about executed query
* [SHOW PROFILE](Node_info_and_management/Profiling/Query_profile.md) - Shows profiling information about executed query
* [SHOW PLAN](Searching/Full_text_matching/Profiling.md#Profiling-the-query-tree-in-SQL) - Shows query execution plan after the query was executed
* [SHOW WARNINGS](Node_info_and_management/SHOW_WARNINGS.md) - Shows warnings from the latest query

##### Flushing misc things
* [FLUSH ATTRIBUTES](Securing_and_compacting_a_table/Flushing_attributes.md) - Forces flushing updated attributes to disk
* [FLUSH HOSTNAMES](Securing_and_compacting_a_table/Flushing_hostnames.md) - Renews IPs associates to agent host names
* [FLUSH LOGS](Logging/Rotating_query_and_server_logs.md) - Initiates reopen of searchd log and query log files (similar to USR1)

##### Real-time table optimization
* [FLUSH RAMCHUNK](Securing_and_compacting_a_table/Flushing_RAM_chunk_to_a_new_disk_chunk.md#FLUSH-RAMCHUNK) - Force creating a new disk chunk
* [FLUSH TABLE](Securing_and_compacting_a_table/Flushing_RAM_chunk_to_disk.md#FLUSH-TABLE) - Flushes real-time table RAM chunk to disk
* [OPTIMIZE TABLE](Securing_and_compacting_a_table/Compacting_a_table.md#OPTIMIZE-TABLE) - Enqueues real-time table for optimization

##### Importing to a real-time table
* [ATTACH TABLE](Data_creation_and_modification/Adding_data_from_external_storages/Adding_data_to_tables/Attaching_a_plain_table_to_RT_table.md) - Moves data from a plain table to a real-time table
* [IMPORT TABLE](Data_creation_and_modification/Adding_data_from_external_storages/Adding_data_to_tables/Importing_table.md) - Imports previously created RT or PQ table into a server running in the RT mode

##### Replication
* [JOIN CLUSTER](Creating_a_cluster/Setting_up_replication/Joining_a_replication_cluster.md) - Joins a replication cluster
* [ALTER CLUSTER](Creating_a_cluster/Setting_up_replication/Managing_replication_nodes.md) - Adds/deletes a table to a replication cluster
* [SET CLUSTER](Creating_a_cluster/Setting_up_replication/Setting_up_replication.md#Cluster-parameters) - Changes replication cluster settings
* [DELETE CLUSTER](Creating_a_cluster/Setting_up_replication/Deleting_a_replication_cluster.md) - Deletes a replication cluster

##### Plain table rotate
* [RELOAD TABLE](Data_creation_and_modification/Adding_data_from_external_storages/Rotating_a_table.md#RELOAD-TABLE) - Rotates a plain table
* [RELOAD TABLES](Data_creation_and_modification/Adding_data_from_external_storages/Rotating_a_table.md#RELOAD-TABLE) - Rotates all plain tables

##### Transactions
* [BEGIN](Data_creation_and_modification/Transactions.md#BEGIN,-COMMIT,-and-ROLLBACK) - Begins a transaction
* [COMMIT](Data_creation_and_modification/Transactions.md#BEGIN,-COMMIT,-and-ROLLBACK) - Finishes a transaction
* [ROLLBACK](Data_creation_and_modification/Transactions.md#BEGIN,-COMMIT,-and-ROLLBACK) - Rolls back a transaction

##### CALL
* [CALL SUGGEST, CALL QSUGGEST](Searching/Spell_correction.md#CALL-QSUGGEST,-CALL-SUGGEST) - Suggests spell-corrected words
* [CALL SNIPPETS](Searching/Highlighting.md) - Builds a highlighted results snippet from provided data and query
* [CALL PQ](Searching/Percolate_query.md) - Runs a percolate query
* [CALL KEYWORDS](Searching/Autocomplete.md#CALL-KEYWORDS) - Used to check how keywords are tokenized. Also allows to retrieve tokenized forms of provided keywords

##### Plugins
* [CREATE FUNCTION](Extensions/UDFs_and_Plugins/UDF/Creating_a_function.md) - Installs a user-defined function (UDF)
* [DROP FUNCTION](Extensions/UDFs_and_Plugins/UDF/Deleting_a_function.md) - Drops a user-defined function (UDF)
* [CREATE PLUGIN](Extensions/UDFs_and_Plugins/Plugins/Creating_a_plugin.md) - Installs a plugin
* [DROP PLUGIN](Extensions/UDFs_and_Plugins/Plugins/Deleting_a_plugin.md) - Drops a plugin
* [RELOAD PLUGINS](Extensions/UDFs_and_Plugins/Plugins/Reloading_plugins.md) - Reloads all plugins from a given library

##### Server status
* [SHOW STATUS](Node_info_and_management/Node_status.md#SHOW-STATUS) - Displays a number of useful performance counters
* [SHOW THREADS](Node_info_and_management/SHOW_THREADS.md) - Lists all currently active client threads
* [SHOW VARIABLES](Node_info_and_management/SHOW_VARIABLES.md) - Lists server-wide variables and their values

### HTTP endpoints
* [/sql](Connecting_to_the_server/HTTP.md#SQL-over-HTTP) - Allows running an SQL statement over HTTP
* [/cli](Connecting_to_the_server/HTTP.md#/cli) - HTTP command line interface
* [/insert](Data_creation_and_modification/Adding_documents_to_a_table/Adding_documents_to_a_real-time_table.md) - Inserts a document into a real-time table
* [/pq/tbl_name/doc](Data_creation_and_modification/Adding_documents_to_a_table/Adding_rules_to_a_percolate_table.md#Adding-rules-to-a-percolate-table) - Inserts a PQ rule into a percolate table
* [/update](Data_creation_and_modification/Updating_documents/UPDATE.md#Updates-via-HTTP-JSON) - Updates a document in a real-time table
* [/replace](Data_creation_and_modification/Updating_documents/REPLACE.md) - Replaces a document in a real-time table
* [/pq/tbl_name/doc/N?refresh=1](Data_creation_and_modification/Adding_documents_to_a_table/Adding_rules_to_a_percolate_table.md#Adding-rules-to-a-percolate-table) - Replaces a PQ rule in a percolate table
* [/delete](Data_creation_and_modification/Deleting_documents.md) - Deletes a document in a table
* [/bulk](Data_creation_and_modification/Updating_documents/UPDATE.md#Bulk-updates) - Perform several insert, update or delete operations in a single call. More about bulk inserts [here](Data_creation_and_modification/Adding_documents_to_a_table/Adding_documents_to_a_real-time_table.md).
* [/search](Searching/Full_text_matching/Basic_usage.md#HTTP-JSON) - Performs search
* [/pq/tbl_name/search](Searching/Percolate_query.md) - Performs reverse search in a percolate table

### Common things
* [data types](Creating_a_table/Data_types.md)
* [engine](Creating_a_table/Data_types.md)
* [plain mode](Read_this_first.md#Real-time-mode-vs-plain-mode)
* [real-time mode](Read_this_first.md#Real-time-mode-vs-plain-mode)

##### Common table settings
* [access_plain_attrs](Server_settings/Searchd.md#access_plain_attrs)
* [access_blob_attrs](Server_settings/Searchd.md#access_blob_attrs)
* [access_doclists](Server_settings/Searchd.md#access_doclists)
* [access_hitlists](Server_settings/Searchd.md#access_hitlists)
* [attr_update_reserve](Data_creation_and_modification/Updating_documents/UPDATE.md#attr_update_reserve)
* [bigram_freq_words](Creating_a_table/NLP_and_tokenization/Low-level_tokenization.md#bigram_freq_words)
* [bigram_index](Creating_a_table/NLP_and_tokenization/Low-level_tokenization.md#bigram_freq_words)
* [blend_chars](Creating_a_table/NLP_and_tokenization/Low-level_tokenization.md#bigram_freq_words)
* [blend_mode](Creating_a_table/NLP_and_tokenization/Low-level_tokenization.md#bigram_freq_words)
* [charset_table](Creating_a_table/NLP_and_tokenization/Low-level_tokenization.md#bigram_freq_words)
* [dict](Creating_a_table/NLP_and_tokenization/Low-level_tokenization.md#bigram_freq_words)
* [docstore_block_size](Creating_a_table/Local_tables/Plain_and_real-time_table_settings.md#General-syntax-of-CREATE-TABLE)
* [docstore_compression](Creating_a_table/Local_tables/Plain_and_real-time_table_settings.md#General-syntax-of-CREATE-TABLE)
* [docstore_compression_level](Creating_a_table/Local_tables/Plain_and_real-time_table_settings.md#General-syntax-of-CREATE-TABLE)
* [embedded_limit](Creating_a_table/NLP_and_tokenization/Low-level_tokenization.md#bigram_freq_words)
* [exceptions](Creating_a_table/NLP_and_tokenization/Low-level_tokenization.md#bigram_freq_words)
* [expand_keywords](Searching/Options.md#expand_keywords)
* [global_idf](Searching/Options.md#global_idf)
* [hitless_words](Creating_a_table/NLP_and_tokenization/Low-level_tokenization.md#bigram_freq_words)
* [html_index_attrs](Creating_a_table/NLP_and_tokenization/Low-level_tokenization.md#bigram_freq_words)
* [html_remove_elements](Creating_a_table/NLP_and_tokenization/Low-level_tokenization.md#bigram_freq_words)
* [html_strip](Creating_a_table/NLP_and_tokenization/Low-level_tokenization.md#bigram_freq_words)
* [ignore_chars](Creating_a_table/NLP_and_tokenization/Low-level_tokenization.md#bigram_freq_words)
* [index_exact_words](Creating_a_table/NLP_and_tokenization/Low-level_tokenization.md#bigram_freq_words)
* [index_field_lengths](Creating_a_table/NLP_and_tokenization/Low-level_tokenization.md#bigram_freq_words)
* [index_sp](Creating_a_table/NLP_and_tokenization/Low-level_tokenization.md#bigram_freq_words)
* [index_token_filter](Creating_a_table/NLP_and_tokenization/Low-level_tokenization.md#bigram_freq_words)
* [index_zones](Creating_a_table/NLP_and_tokenization/Low-level_tokenization.md#bigram_freq_words)
* [infix_fields](Creating_a_table/NLP_and_tokenization/Low-level_tokenization.md#bigram_freq_words)
* [inplace_enable](Creating_a_table/Local_tables/Plain_and_real-time_table_settings.md#General-syntax-of-CREATE-TABLE)
* [inplace_hit_gap](Creating_a_table/Local_tables/Plain_and_real-time_table_settings.md#General-syntax-of-CREATE-TABLE)
* [inplace_reloc_factor](Creating_a_table/Local_tables/Plain_and_real-time_table_settings.md#General-syntax-of-CREATE-TABLE)
* [inplace_write_factor](Creating_a_table/Local_tables/Plain_and_real-time_table_settings.md#General-syntax-of-CREATE-TABLE)
* [killlist_target](Creating_a_table/Local_tables/Plain_and_real-time_table_settings.md#General-syntax-of-CREATE-TABLE)
* [max_substring_len](Creating_a_table/NLP_and_tokenization/Low-level_tokenization.md#bigram_freq_words)
* [min_infix_len](Creating_a_table/NLP_and_tokenization/Low-level_tokenization.md#bigram_freq_words)
* [min_prefix_len](Creating_a_table/NLP_and_tokenization/Low-level_tokenization.md#bigram_freq_words)
* [min_stemming_len](Creating_a_table/NLP_and_tokenization/Low-level_tokenization.md#bigram_freq_words)
* [min_word_len](Creating_a_table/NLP_and_tokenization/Low-level_tokenization.md#bigram_freq_words)
* [morphology](Searching/Options.md#morphology)
* [morphology_skip_fields](Creating_a_table/NLP_and_tokenization/Low-level_tokenization.md#bigram_freq_words)
* [ngram_chars](Creating_a_table/NLP_and_tokenization/Low-level_tokenization.md#bigram_freq_words)
* [ngram_len](Creating_a_table/NLP_and_tokenization/Low-level_tokenization.md#bigram_freq_words)
* [overshort_step](Creating_a_table/NLP_and_tokenization/Low-level_tokenization.md#bigram_freq_words)
* [path](Creating_a_table/Local_tables/Plain_and_real-time_table_settings.md#General-syntax-of-CREATE-TABLE)
* [phrase_boundary](Creating_a_table/NLP_and_tokenization/Low-level_tokenization.md#bigram_freq_words)
* [phrase_boundary_step](Creating_a_table/NLP_and_tokenization/Low-level_tokenization.md#bigram_freq_words)
* [prefix_fields](Creating_a_table/NLP_and_tokenization/Low-level_tokenization.md#bigram_freq_words)
* [preopen](Creating_a_table/Local_tables/Plain_and_real-time_table_settings.md#General-syntax-of-CREATE-TABLE)
* [read_buffer_docs](Creating_a_table/Local_tables/Plain_and_real-time_table_settings.md#General-syntax-of-CREATE-TABLE)
* [read_buffer_hits](Creating_a_table/Local_tables/Plain_and_real-time_table_settings.md#General-syntax-of-CREATE-TABLE)
* [regexp_filter](Creating_a_table/NLP_and_tokenization/Low-level_tokenization.md#bigram_freq_words)
* [stopwords](Creating_a_table/NLP_and_tokenization/Low-level_tokenization.md#bigram_freq_words)
* [stopword_step](Creating_a_table/NLP_and_tokenization/Low-level_tokenization.md#bigram_freq_words)
* [stopwords_unstemmed](Creating_a_table/NLP_and_tokenization/Low-level_tokenization.md#bigram_freq_words)
* [type](Creating_a_table/Local_tables/Plain_and_real-time_table_settings.md#General-syntax-of-CREATE-TABLE)
* [wordforms](Creating_a_table/NLP_and_tokenization/Low-level_tokenization.md#bigram_freq_words)

##### Plain table settings
* [source](Creating_a_table/Local_tables/Plain_and_real-time_table_settings.md#General-syntax-of-CREATE-TABLE)
* [stored_fields](Creating_a_table/Local_tables/Plain_and_real-time_table_settings.md#General-syntax-of-CREATE-TABLE)
* [stored_only_fields](Creating_a_table/Local_tables/Plain_and_real-time_table_settings.md#General-syntax-of-CREATE-TABLE)
* [columnar_attrs](Creating_a_table/Local_tables/Plain_and_real-time_table_settings.md#General-syntax-of-CREATE-TABLE)

##### Distributed table settings
* [local](Creating_a_table/Creating_a_distributed_table/Creating_a_local_distributed_table.md)
* [agent](Creating_a_table/Creating_a_distributed_table/Remote_tables.md#agent)
* [agent_connect_timeout](Creating_a_table/Creating_a_distributed_table/Remote_tables.md#agent)
* [agent_blackhole](Creating_a_table/Creating_a_distributed_table/Remote_tables.md#agent)
* [agent_persistent](Creating_a_table/Creating_a_distributed_table/Remote_tables.md#agent)
* [agent_query_timeout](Searching/Options.md#agent_query_timeout)
* [agent_retry_count](Creating_a_table/Creating_a_distributed_table/Remote_tables.md#agent)
* [ha_strategy](Creating_a_cluster/Remote_nodes/Load_balancing.md#ha_strategy)
* [mirror_retry_count](Creating_a_table/Creating_a_distributed_table/Remote_tables.md#agent)

##### RT table settings
* [rt_attr_bigint](Creating_a_table/Local_tables/Plain_and_real-time_table_settings.md#General-syntax-of-CREATE-TABLE)
* [rt_attr_bool](Creating_a_table/Local_tables/Plain_and_real-time_table_settings.md#General-syntax-of-CREATE-TABLE)
* [rt_attr_float](Creating_a_table/Local_tables/Plain_and_real-time_table_settings.md#General-syntax-of-CREATE-TABLE)
* [rt_attr_json](Creating_a_table/Local_tables/Plain_and_real-time_table_settings.md#General-syntax-of-CREATE-TABLE)
* [rt_attr_multi_64](Creating_a_table/Local_tables/Plain_and_real-time_table_settings.md#General-syntax-of-CREATE-TABLE)
* [rt_attr_multi](Creating_a_table/Local_tables/Plain_and_real-time_table_settings.md#General-syntax-of-CREATE-TABLE)
* [rt_attr_string](Creating_a_table/Local_tables/Plain_and_real-time_table_settings.md#General-syntax-of-CREATE-TABLE)
* [rt_attr_timestamp](Creating_a_table/Local_tables/Plain_and_real-time_table_settings.md#General-syntax-of-CREATE-TABLE)
* [rt_attr_uint](Creating_a_table/Local_tables/Plain_and_real-time_table_settings.md#General-syntax-of-CREATE-TABLE)
* [rt_field](Creating_a_table/Local_tables/Plain_and_real-time_table_settings.md#General-syntax-of-CREATE-TABLE)
* [rt_mem_limit](Creating_a_table/Local_tables/Plain_and_real-time_table_settings.md#General-syntax-of-CREATE-TABLE)

## Full-text search operators
* [OR](Searching/Full_text_matching/Operators.md#OR-operator)
* [MAYBE](Searching/Full_text_matching/Operators.md#MAYBE-operator)
* [NOT](Searching/Full_text_matching/Operators.md#Negation-operator) - operator NOT
* [@field](Searching/Full_text_matching/Operators.md#Field-search-operator) - field search operator
* [@field%5BN%5D](Searching/Full_text_matching/Operators.md#Field-search-operator) - field position limit modifier
* [@(field1,field2,...)](Searching/Full_text_matching/Operators.md#Field-search-operator) - multiple-field search operator
* [@!field](Searching/Full_text_matching/Operators.md#Field-search-operator) - ignore field search operator
* [@!(field1,field2,...)](Searching/Full_text_matching/Operators.md#Field-search-operator) - ignore multiple-field search operator
* [@*](Searching/Full_text_matching/Operators.md#Field-search-operator) - all-field search operator
* ["word1 word2 ... "](Searching/Full_text_matching/Operators.md#Phrase-search-operator) - phrase search operator
* ["word1 word2 ... "~N](Searching/Full_text_matching/Operators.md#Proximity-search-operator) - proximity search operator
* ["word1 word2 ... "/N](Searching/Full_text_matching/Operators.md#Quorum-matching-operator) - quorum matching operator
* [word1 <<< word2 <<< word3](Searching/Full_text_matching/Operators.md#Strict-order-operator) - strict order operator
* [=word1](Searching/Full_text_matching/Operators.md#Exact-form-modifier) - exact form modifier
* [^word1](Searching/Full_text_matching/Operators.md#Field-start-and-field-end-modifier) - field-start modifier
* [word2$](Searching/Full_text_matching/Operators.md#Field-start-and-field-end-modifier) - field-end modifier
* [word^N](Searching/Full_text_matching/Operators.md#IDF-boost-modifier) - keyword IDF boost modifier
* [word1 NEAR/N word2](Searching/Full_text_matching/Operators.md#NEAR-operator) - NEAR, generalized proximity operator
* [word1 NOTNEAR/N word2](Searching/Full_text_matching/Operators.md#NOTNEAR-operator) - NOTNEAR, negative assertion operator
* [word1 SENTENCE word2 SENTENCE "word3 word4"](Searching/Full_text_matching/Operators.md#SENTENCE-and-PARAGRAPH-operators) - SENTENCE operator
* [word1 PARAGRAPH word2 PARAGRAPH "word3 word4"](Searching/Full_text_matching/Operators.md#SENTENCE-and-PARAGRAPH-operators) - PARAGRAPH operator
* [ZONE:(h3,h4)](Searching/Full_text_matching/Operators.md#ZONE-limit-operator) - ZONE limit operator
* [ZONESPAN:(h2)](Searching/Full_text_matching/Operators.md#ZONESPAN-limit-operator) - ZONESPAN limit operator
* [@@relaxed](Searching/Full_text_matching/Operators.md#Field-search-operator) - suppresses errors about missing fields

## Functions
##### Mathematical
* [ABS()](Functions/Mathematical_functions.md#ABS%28%29) - Returns absolute value
* [ATAN2()](Functions/Mathematical_functions.md#ATAN2%28%29) - Returns arctangent function of two arguments
* [BITDOT()](Functions/Mathematical_functions.md#BITDOT%28%29) - Returns sum of products of an each bit of a mask multiplied with its weight
* [CEIL()](Functions/Mathematical_functions.md#CEIL%28%29) - Returns smallest integer value greater or equal to the argument
* [COS()](Functions/Mathematical_functions.md#COS%28%29) - Returns cosine of the argument
* [CRC32()](Functions/Mathematical_functions.md#CRC32%28%29) - Returns CRC32 value of the argument
* [EXP()](Functions/Mathematical_functions.md#EXP%28%29) - Returns exponent of the argument
* [FIBONACCI()](Functions/Mathematical_functions.md#FIBONACCI%28%29) - Returns the N-th Fibonacci number, where N is the integer argument
* [FLOOR()](Functions/Mathematical_functions.md#FLOOR%28%29) - Returns the largest integer value lesser or equal to the argument
* [GREATEST()](Functions/Mathematical_functions.md#GREATEST%28%29) - Takes JSON/MVA array as the argument and returns the greatest value in that array
* [IDIV()](Functions/Mathematical_functions.md#IDIV%28%29) - Returns result of an integer division of the first argument by the second argument
* [LEAST()](Functions/Mathematical_functions.md#LEAST%28%29) - Takes JSON/MVA array as the argument, and returns the least value in that array
* [LN()](Functions/Mathematical_functions.md#LN%28%29) - Returns natural logarithm of the argument
* [LOG10()](Functions/Mathematical_functions.md#LOG10%28%29) - Returns common logarithm of the argument
* [LOG2()](Functions/Mathematical_functions.md#LOG2%28%29) - Returns binary logarithm of the argument
* [MAX()](Functions/Mathematical_functions.md#MAX%28%29) - Returns the bigger of two arguments
* [MIN()](Functions/Mathematical_functions.md#MIN%28%29) - Returns the smaller of two arguments
* [POW()](Functions/Mathematical_functions.md#POW%28%29) - Returns the first argument raised to the power of the second argument
* [RAND()](Functions/Mathematical_functions.md#RAND%28%29) - Returns random float between 0..1
* [SIN()](Functions/Mathematical_functions.md#SIN%28%29) - Returns sine of the argument
* [SQRT()](Functions/Mathematical_functions.md#SQRT%28%29) - Returns square root of the argument


##### Searching and ranking
* [BM25F()](Functions/Searching_and_ranking_functions.md#BM25F%28%29) - Returns precise BM25F formula value
* [EXIST()](Functions/Searching_and_ranking_functions.md#EXIST%28%29) - Replaces non-existing columns with default values
* [GROUP_CONCAT()](Searching/Grouping.md#GROUP_CONCAT%28field%29) - Produces a comma-separated list of the attribute values of all documents in the group
* [HIGHLIGHT()](Searching/Highlighting.md) - Highlights search results
* [MIN_TOP_SORTVAL()](Functions/Searching_and_ranking_functions.md#MIN_TOP_SORTVAL%28%29) - Returns sort key value of the worst found element in the current top-N matches
* [MIN_TOP_WEIGHT()](Functions/Searching_and_ranking_functions.md#MIN_TOP_WEIGHT%28%29) - Returns weight of the worst found element in the current top-N matches
* [PACKEDFACTORS()](Functions/Searching_and_ranking_functions.md#PACKEDFACTORS%28%29) - Outputs weighting factors
* [REMOVE_REPEATS()](Functions/Searching_and_ranking_functions.md#REMOVE_REPEATS%28%29) - Removes repeated adjusted rows with the same 'column' value
* [WEIGHT()](Functions/Searching_and_ranking_functions.md#WEIGHT%28%29) - Returns fulltext match score
* [ZONESPANLIST()](Functions/Searching_and_ranking_functions.md#ZONESPANLIST%28%29) - Returns pairs of matched zone spans
* [QUERY()](Functions/Searching_and_ranking_functions.md#QUERY%28%29) - Returns current full-text query

##### Type casting
* [BIGINT()](Functions/Type_casting_functions.md#BIGINT%28%29) - Forcibly promotes the integer argument to 64-bit type
* [DOUBLE()](Functions/Type_casting_functions.md#DOUBLE%28%29) - Forcibly promotes given argument to floating point type
* [INTEGER()](Functions/Type_casting_functions.md#INTEGER%28%29) - Forcibly promotes given argument to 64-bit signed type
* [TO_STRING()](Functions/Type_casting_functions.md#TO_STRING%28%29) - Forcibly promotes the argument to string type
* [UINT()](Functions/Type_casting_functions.md#UINT%28%29) - Converts the given argument to 32-bit unsigned integer type
* [UINT64()](Functions/Type_casting_functions.md#UINT64%28%29) - Converts the given argument to 64-bit unsigned integer type
* [SINT()](Functions/Type_casting_functions.md#SINT%28%29) - Interprets 32-bit unsigned integer as signed 64-bit integer

##### Arrays and conditions
* [ALL()](Functions/Arrays_and_conditions_functions.md#ALL%28%29) - Returns 1 if condition is true for all elements in the array
* [ANY()](Functions/Arrays_and_conditions_functions.md#ANY%28%29) - Returns 1 if condition is true for any element in the array
* [CONTAINS()](Functions/Arrays_and_conditions_functions.md#CONTAINS%28%29) - Checks whether the (x,y) point is within the given polygon
* [IF()](Functions/Arrays_and_conditions_functions.md#IF%28%29) - Checks whether the 1st argument is equal to 0.0, returns the 2nd argument if it is not zero or the 3rd one when it is
* [IN()](Functions/Arrays_and_conditions_functions.md#IN%28%29) - Returns 1 if the first argument is equal to any of the other arguments, or 0 otherwise
* [INDEXOF()](Functions/Arrays_and_conditions_functions.md#INDEXOF%28%29) - Iterates through all elements in the array and returns index of the first matching element
* [INTERVAL()](Functions/Arrays_and_conditions_functions.md#INTERVAL%28%29) - Returns index of the argument that is less than the first argument
* [LENGTH()](Functions/Arrays_and_conditions_functions.md#LENGTH%28%29) - Returns number of elements in MVA
* [REMAP()](Functions/Arrays_and_conditions_functions.md#REMAP%28%29) - Allows to make some exceptions of expression values depending on the condition values

##### Date and time
* [NOW()](Functions/Date_and_time_functions.md#NOW%28%29) - Returns current timestamp as an INTEGER
* [CURTIME()](Functions/Date_and_time_functions.md#CURTIME%28%29) - Returns current time in local timezone
* [UTC_TIME()](Functions/Date_and_time_functions.md#UTC_TIME%28%29) - Returns current time in UTC timezone
* [UTC_TIMESTAMP()](Functions/Date_and_time_functions.md#UTC_TIMESTAMP%28%29) - Returns current date/time in UTC timezone
* [SECOND()](Functions/Date_and_time_functions.md#SECOND%28%29) - Returns integer second from the timestamp argument
* [MINUTE()](Functions/Date_and_time_functions.md#MINUTE%28%29) - Returns integer minute from the timestamp argument
* [HOUR()](Functions/Date_and_time_functions.md#HOUR%28%29) - Returns integer hour from the timestamp argument
* [DAY()](Functions/Date_and_time_functions.md#DAY%28%29) - Returns integer day from the timestamp argument
* [MONTH()](Functions/Date_and_time_functions.md#MONTH%28%29) - Returns integer month from the timestamp argument
* [YEAR()](Functions/Date_and_time_functions.md#YEAR%28%29) - Returns integer year from the timestamp argument
* [YEARMONTH()](Functions/Date_and_time_functions.md#YEARMONTH%28%29) - Returns integer year and month code from the timestamp argument
* [YEARMONTHDAY()](Functions/Date_and_time_functions.md#YEARMONTHDAY%28%29) - Returns integer year, month and day code from the timestamp argument
* [TIMEDIFF()](Functions/Date_and_time_functions.md#TIMEDIFF%28%29) - Returns difference between the timstamps

##### Geo-spatial
* [GEODIST()](Functions/Geo_spatial_functions.md#GEODIST%28%29) - Computes geosphere distance between two given points
* [GEOPOLY2D()](Functions/Geo_spatial_functions.md#GEOPOLY2D%28%29) - Creates a polygon that takes in account the Earth's curvature
* [POLY2D()](Functions/Geo_spatial_functions.md#POLY2D%28%29) - Creates a simple polygon in plain space

##### String
* [CONCAT()](Functions/String_functions.md#CONCAT%28%29) - Concatenates two or more strings
* [REGEX()](Functions/String_functions.md#REGEX%28%29) - Returns 1 if regular expression matched to string of attribute and 0 otherwise
* [SNIPPET()](Functions/String_functions.md#SNIPPET%28%29) - Highlights search results
* [SUBSTRING_INDEX()](Functions/String_functions.md#SUBSTRING_INDEX%28%29) - Returns a substring of the string before the specified number of delimiter occurs
*
##### Other
* [LAST_INSERT_ID()](Functions/Other_functions.md#LAST_INSERT_ID%28%29) - Returns ids of documents inserted or replaced by last statement in the current session

## Common settings in configuration file
To be put to section `common {}` in configuration file:
* [lemmatizer_base](Server_settings/Common.md#lemmatizer_base) - Lemmatizer dictionaries base path
* [progressive_merge](Server_settings/Common.md#progressive_merge) - Defines order of merging disk chunks in a real-time table
* [json_autoconv_keynames](Server_settings/Common.md#json_autoconv_keynames) - Whether and how to auto-convert key names within JSON attributes
* [json_autoconv_numbers](Server_settings/Common.md#json_autoconv_numbers) - Automatically detects and converts possible JSON strings that represent numbers into numeric attributes
* [on_json_attr_error](Server_settings/Common.md#on_json_attr_error) - What to do if JSON format errors are found
* [plugin_dir](Server_settings/Common.md#plugin_dir) - Location for the dynamic libraries and UDFs

## [Indexer](Data_creation_and_modification/Adding_data_from_external_storages/Plain_tables_creation.md#Indexer-command-line-arguments)
`indexer` is a tool to create [plain tables](Data_creation_and_modification/Adding_data_from_external_storages/Plain_tables_creation.md#Indexer-command-line-arguments)

##### Indexer settings in configuration file
To be put to section `indexer {}` in configuration file:
* [lemmatizer_cache](Data_creation_and_modification/Adding_data_from_external_storages/Plain_tables_creation.md#Indexer-command-line-arguments) - Lemmatizer cache size
* [max_file_field_buffer](Data_creation_and_modification/Adding_data_from_external_storages/Plain_tables_creation.md#Indexer-command-line-arguments) - Maximum file field adaptive buffer size
* [max_iops](Data_creation_and_modification/Adding_data_from_external_storages/Plain_tables_creation.md#Indexer-command-line-arguments) - Maximum indexation I/O operations per second
* [max_iosize](Data_creation_and_modification/Adding_data_from_external_storages/Plain_tables_creation.md#Indexer-command-line-arguments) - Maximum allowed I/O operation size
* [max_xmlpipe2_field](Data_creation_and_modification/Adding_data_from_external_storages/Plain_tables_creation.md#Indexer-command-line-arguments) - Maximum allowed field size for XMLpipe2 source type
* [mem_limit](Data_creation_and_modification/Adding_data_from_external_storages/Plain_tables_creation.md#Indexer-command-line-arguments) - Indexing RAM usage limit
* [on_file_field_error](Data_creation_and_modification/Adding_data_from_external_storages/Plain_tables_creation.md#Indexer-command-line-arguments) - How to handle IO errors in file fields
* [write_buffer](Data_creation_and_modification/Adding_data_from_external_storages/Plain_tables_creation.md#Indexer-command-line-arguments) - Write buffer size
* [ignore_non_plain](Data_creation_and_modification/Adding_data_from_external_storages/Plain_tables_creation.md#Indexer-command-line-arguments) - To ignore warnings about non-plain tables

##### Indexer start parameters
```bash
indexer [OPTIONS] [indexname1 [indexname2 [...]]]
```
* [--all](Data_creation_and_modification/Adding_data_from_external_storages/Plain_tables_creation.md#Indexer-command-line-arguments) - Rebuilds all tables from the config
* [--buildstops](Data_creation_and_modification/Adding_data_from_external_storages/Plain_tables_creation.md#Indexer-command-line-arguments) - Reviews the table source, as if it were indexing the data, and produces a list of the terms that are being indexed.
* [--buildfreqs](Data_creation_and_modification/Adding_data_from_external_storages/Plain_tables_creation.md#Indexer-command-line-arguments) - Adds the quantity present in the table for --buildstops
* [--config, -c](Data_creation_and_modification/Adding_data_from_external_storages/Plain_tables_creation.md#Indexer-command-line-arguments) - Path to configuration file
* [--dump-rows](Data_creation_and_modification/Adding_data_from_external_storages/Plain_tables_creation.md#Indexer-command-line-arguments) - Dumps rows fetched by SQL source(s) into the specified file
* [--help](Data_creation_and_modification/Adding_data_from_external_storages/Plain_tables_creation.md#Indexer-command-line-arguments) - Lists all the parameters
* [--keep-attrs](Data_creation_and_modification/Adding_data_from_external_storages/Plain_tables_creation.md#Indexer-command-line-arguments) - Allows to reuse existing attributes on reindexing
* [--keep-attrs-names](Data_creation_and_modification/Adding_data_from_external_storages/Plain_tables_creation.md#Indexer-command-line-arguments) - Allows to specify attributes to reuse from the existing table
* [--merge-dst-range](Data_creation_and_modification/Adding_data_from_external_storages/Plain_tables_creation.md#Indexer-command-line-arguments) - Runs the filter range given upon merging
* [--merge-killlists](Data_creation_and_modification/Adding_data_from_external_storages/Plain_tables_creation.md#Indexer-command-line-arguments) - Changes the way kill lists are processed when merging tables
* [--merge](Data_creation_and_modification/Adding_data_from_external_storages/Plain_tables_creation.md#Indexer-command-line-arguments) - Merges two plain tables into one
* [--nohup](Data_creation_and_modification/Adding_data_from_external_storages/Plain_tables_creation.md#Indexer-command-line-arguments) - Indexer won't send SIGHUP if this option is on
* [--noprogress](Data_creation_and_modification/Adding_data_from_external_storages/Plain_tables_creation.md#Indexer-command-line-arguments) - Prevents displaying progress details
* [--print-queries](Data_creation_and_modification/Adding_data_from_external_storages/Plain_tables_creation.md#Indexer-command-line-arguments) - Prints out SQL queries that indexer sends to the database
* [--print-rt ](Data_creation_and_modification/Adding_data_from_external_storages/Plain_tables_creation.md#Indexer-command-line-arguments) - Outputs data fetched from sql source(s) as INSERTs to a real-time table
* [--quiet](Data_creation_and_modification/Adding_data_from_external_storages/Plain_tables_creation.md#Indexer-command-line-arguments) - Prevents displaying anything
* [--rotate](Data_creation_and_modification/Adding_data_from_external_storages/Plain_tables_creation.md#Indexer-command-line-arguments) - Forces tables rotation after all the tables are built
* [--sighup-each](Data_creation_and_modification/Adding_data_from_external_storages/Plain_tables_creation.md#Indexer-command-line-arguments) - Forces rotation of each table after it's built
* [-v](Data_creation_and_modification/Adding_data_from_external_storages/Plain_tables_creation.md#Indexer-command-line-arguments) - Shows indexer version

## Table converter from Manticore v2 / Sphinx v2
`index_converter` is a tool for converting tables created with Sphinx/Manticore Search 2.x to Manticore Search 3.x table format.
```bash
index_converter {--config /path/to/config|--path}
```
##### Table converter start parameters
* [--config, -c](Installation/Migration_from_Sphinx.md#index_converter) - Path to tables configuration file
* [--index](Installation/Migration_from_Sphinx.md#index_converter) - Specifies which table should be converted
* [--path](Installation/Migration_from_Sphinx.md#index_converter) - Defines path containing table(s) instead of the configuration file
* [--strip-path](Installation/Migration_from_Sphinx.md#index_converter) - Strips path from filenames referenced by table
* [--large-docid](Installation/Migration_from_Sphinx.md#index_converter) - Allows to convert documents with ids larger than 2^63
* [--output-dir](Installation/Migration_from_Sphinx.md#index_converter) - Writes the new files in a chosen folder
* [--all](Installation/Migration_from_Sphinx.md#index_converter) - Converts all tables from the configuration file / path
* [--killlist-target](Installation/Migration_from_Sphinx.md#index_converter) - Sets the target tables for which kill-lists will be applied

## [Searchd](Starting_the_server/Manually.md)
`searchd` is a Manticore server.

##### Searchd settings in a configuration file
To be put to section `searchd {}` in configuration file:
  * [access_blob_attrs](Server_settings/Searchd.md#access_blob_attrs) - Specifies how table's blob attributes file is accessed
  * [access_doclists](Server_settings/Searchd.md#access_doclists) - Specifies how table's doclists file is accessed
  * [access_hitlists](Server_settings/Searchd.md#access_hitlists) - Specifies how table's hitlists file is accessed
  * [access_plain_attrs](Server_settings/Searchd.md#access_plain_attrs) - Specifies how search server will access table's plain attributes
  * [agent_connect_timeout](Creating_a_table/Creating_a_distributed_table/Remote_tables.md#agent_connect_timeout) - Remote agent connection timeout
  * [agent_query_timeout](Searching/Options.md#agent_query_timeout) - Remote agent query timeout
  * [agent_retry_count](Creating_a_table/Creating_a_distributed_table/Remote_tables.md#agent_connect_timeout) - Specifies how many times Manticore will try to connect and query remote agents
  * [agent_retry_delay](Creating_a_table/Creating_a_distributed_table/Remote_tables.md#agent) - Specifies the delay before retrying to query a remote agent in case it fails
  * [attr_flush_period](Data_creation_and_modification/Updating_documents/UPDATE.md#attr_flush_period) - Defines time period between flushing updated attributes to disk
  * [binlog_flush](Server_settings/Searchd.md#binlog_flush) - Binary log transaction flush/sync mode
  * [binlog_max_log_size](Server_settings/Searchd.md#binlog_max_log_size) - Maximum binary log file size
  * [binlog_path](Server_settings/Searchd.md#binlog_path) - Binary log files path
  * [client_timeout](Creating_a_table/Creating_a_distributed_table/Remote_tables.md#agent) - Maximum time to wait between requests when using persistent connections
  * [collation_libc_locale](Server_settings/Searchd.md#collation_libc_locale) - Server libc locale
  * [collation_server](Server_settings/Searchd.md#collation_server) - Default server collation
  * [data_dir](Server_settings/Searchd.md#data_dir) - Path to data directory where Manticore stores everything ([RT mode](Creating_a_table/Local_tables.md#Online-schema-management-%28RT-mode%29))
  * [docstore_cache_size](Server_settings/Searchd.md#docstore_cache_size) - Maximum size of document blocks from document storage that are held in memory
  * [expansion_limit](Creating_a_table/NLP_and_tokenization/Low-level_tokenization.md#bigram_freq_words) - Maximum number of expanded keywords for a single wildcard
  * [grouping_in_utc](Server_settings/Searchd.md#grouping_in_utc) - Turns on using UTC timezone where grouping time fields
  * [ha_period_karma](Server_settings/Searchd.md#ha_period_karma) - Agent mirror statistics window size
  * [ha_ping_interval](Creating_a_cluster/Remote_nodes/Load_balancing.md#ha_ping_interval) - Interval between agent mirror pings
  * [hostname_lookup](Creating_a_table/Creating_a_distributed_table/Remote_tables.md#agent) - Hostnames renew strategy
  * [jobs_queue_size](Server_settings/Searchd.md#jobs_queue_size) - Defines how many "jobs" can be in the queue at the same time
  * [listen](Server_settings/Searchd.md#listen) - Specifies IP address and port or Unix-domain socket path, that searchd will listen on
  * [listen_backlog](Server_settings/Searchd.md#listen_backlog) - TCP listen backlog
  * [listen_tfo](Creating_a_table/Creating_a_distributed_table/Remote_tables.md#agent) - Allows TCP_FASTOPEN flag for all listeners
  * [log](Server_settings/Searchd.md#log) - Path to Manticore server log file
  * [max_batch_queries](Server_settings/Searchd.md#max_batch_queries) - Limits the amount of queries per batch
  * [max_connections](Server_settings/Searchd.md#max_connections) - Maximum amount of active connections
  * [max_filters](Server_settings/Searchd.md#max_filters) - Maximum allowed per-query filter count
  * [max_filter_values](Server_settings/Searchd.md#max_filter_values) - Maximum allowed per-filter values count
  * [max_open_files](Server_settings/Searchd.md#max_open_files) - Maximum num of files which allowed to be opened by server
  * [max_packet_size](Server_settings/Searchd.md#max_packet_size) - Maximum allowed network packet size
  * [mysql_version_string](Server_settings/Searchd.md#mysql_version_string) - Server version string to return via MySQL protocol
  * [net_throttle_accept](Server_settings/Searchd.md#net_throttle_accept) - Defines how many clients are accepted on each iteration of the network loop
  * [net_throttle_action](Server_settings/Searchd.md#net_throttle_action)  - Defines how many requests are processed on each iteration of the network loop
  * [net_wait_tm](Server_settings/Searchd.md#net_wait_tm) - Controls busy loop interval of a network thread
  * [net_workers](Server_settings/Searchd.md#net_workers) - Number of network threads
  * [network_timeout](Server_settings/Searchd.md#network_timeout) - Network timeout for requests from clients
  * [node_address](Server_settings/Searchd.md#node_address) - Specifies network address of the node
  * [persistent_connections_limit](Creating_a_table/Creating_a_distributed_table/Remote_tables.md#agent) - Maximum number of simultaneous persistent connections to remote persistent agents
  * [pid_file](Server_settings/Searchd.md#pid_file) - Path to Manticore server pid file
  * [predicted_time_costs](Server_settings/Searchd.md#predicted_time_costs) - Costs for the query time prediction model
  * [preopen_indexes](Server_settings/Searchd.md#preopen_tables) - Whether to forcibly preopen all tables on startup
  * [pseudo_sharding](Server_settings/Searchd.md#pseudo_sharding) - Enables pseudo-sharding for search queries to plain and real-time tables
  * [qcache_max_bytes](Server_settings/Searchd.md#qcache_max_bytes) - Maximum RAM allocated for cached result sets
  * [qcache_thresh_msec](Server_settings/Searchd.md#qcache_thresh_msec) - Minimum wall time threshold for a query result to be cached
  * [qcache_ttl_sec](Server_settings/Searchd.md#qcache_ttl_sec) - Expiration period for a cached result set
  * [query_log](Server_settings/Searchd.md#query_log) - Path to query log file
  * [query_log_format](Server_settings/Searchd.md#query_log_format) - Query log format
  * [query_log_min_msec](Server_settings/Searchd.md#query_log_min_msec) - Prevents logging too fast queries
  * [query_log_mode](Server_settings/Searchd.md#query_log_mode) - Query log file permissions mode
  * [read_buffer_docs](Creating_a_table/Local_tables/Plain_and_real-time_table_settings.md#read_buffer_docs) - Per-keyword read buffer size for document lists
  * [read_buffer_hits](Creating_a_table/Local_tables/Plain_and_real-time_table_settings.md#read_buffer_docs) - Per-keyword read buffer size for hit lists
  * [read_unhinted](Server_settings/Searchd.md#read_unhinted) - Unhinted read size
  * [rt_flush_period](Server_settings/Searchd.md#rt_flush_period) - How often Manticore flush real-time tables' RAM chunks to disk
  * [rt_merge_iops](Server_settings/Searchd.md#rt_merge_iops) - Maximum number of I/O operations (per second) that real-time chunks merging thread is allowed to do
  * [rt_merge_maxiosize](Server_settings/Searchd.md#rt_merge_maxiosize) - Maximum size of an I/O operation that real-time chunks merging thread is allowed to do
  * [seamless_rotate](Server_settings/Searchd.md#seamless_rotate) - Prevents searchd stalls while rotating tables with huge amounts of data to precache
  * [secondary_indexes](Server_settings/Searchd.md#secondary_indexes) - Enables using secondary indexes for search queries
  * [server_id](Server_settings/Searchd.md#server_id) - Server identifier used as a seed to generate a unique document ID
  * [shutdown_timeout](Server_settings/Searchd.md#shutdown_timeout) - Searchd `--stopwait` timeout
  * [shutdown_token](Server_settings/Searchd.md#shutdown_token) - SHA1 hash of the password required to invoke `shutdown` command from VIP SQL connection
  * [snippets_file_prefix](Creating_a_table/Creating_a_distributed_table/Remote_tables.md#agent) - Prefix to prepend to the local file names when generating snippets in `load_files` mode
  * [sphinxql_state](Server_settings/Searchd.md#sphinxql_state) - Path to file where current SQL state will be serialized
  * [sphinxql_timeout](Server_settings/Searchd.md#sphinxql_timeout) - Maximum time to wait between requests from a mysql client
  * [ssl_ca](Server_settings/Searchd.md#ssl_ca) - Path to SSL Certificate Authority certificate file
  * [ssl_cert](Server_settings/Searchd.md#ssl_cert) - Path to server's SSL certificate
  * [ssl_key](Server_settings/Searchd.md#ssl_key) - Path to SSL certificate key of the server
  * [subtree_docs_cache](Server_settings/Searchd.md#subtree_docs_cache) - Maximum common subtree document cache size
  * [subtree_hits_cache](Server_settings/Searchd.md#subtree_hits_cache) - Maximum common subtree hit cache size, per-query
  * [thread_stack](Server_settings/Searchd.md#thread_stack) - Maximum stack size for a job
  * [unlink_old](Server_settings/Searchd.md#unlink_old) - Whether to unlink .old table copies on successful rotation
  * [watchdog](Server_settings/Searchd.md#watchdog) - Whether to enable or disable Manticore server watchdog

##### Searchd start parameters
```bash
searchd [OPTIONS]
```
* [--config, -c](Starting_the_server/Manually.md#searchd-command-line-options) - Path to configuration file
* [--console](Starting_the_server/Manually.md#searchd-command-line-options) - Forces running in console mode
* [--coredump](Starting_the_server/Manually.md#searchd-command-line-options) - Enables saving core dump on crash
* [--cpustats](Starting_the_server/Manually.md#searchd-command-line-options) - Enables CPU time reporting
* [--delete](Starting_the_server/Manually.md#searchd-command-line-options) - Removes Manticore service from Microsoft Management Console and other places where the services are registered
* [--force-preread](Starting_the_server/Manually.md#searchd-command-line-options) - Forbids the server to serve any incoming connection until pre-reading of the table files completes
* [--help, -h](Starting_the_server/Manually.md#searchd-command-line-options) - Lists all the parameters
* [--table (--index)](Starting_the_server/Manually.md#searchd-command-line-options) - Forces serving only the specified table
* [--install](Starting_the_server/Manually.md#searchd-command-line-options) - Installs searchd as a service into Microsoft Management Console
* [--iostats](Starting_the_server/Manually.md#searchd-command-line-options) - Enables input/output reporting
* [--listen, -l](Starting_the_server/Manually.md#searchd-command-line-options) - Overrides [listen](Server_settings/Searchd.md#listen) from the configuration file
* [--logdebug, --logdebugv, --logdebugvv](Starting_the_server/Manually.md#searchd-command-line-options) - Enables additional debug output in the server log
* [--logreplication](Starting_the_server/Manually.md#searchd-command-line-options) - Enables additional replication debug output in the server log
* [--new-cluster](Starting_the_server/Manually.md#searchd-command-line-options) - Bootstraps a replication cluster and makes the server a reference node with [cluster restart](Creating_a_cluster/Setting_up_replication/Restarting_a_cluster.md) protection
* [--new-cluster-force](Starting_the_server/Manually.md#searchd-command-line-options) - Bootstraps a replication cluster and makes the server a reference node bypassing [cluster restart](Creating_a_cluster/Setting_up_replication/Restarting_a_cluster.md) protection
* [--nodetach](Starting_the_server/Manually.md#searchd-command-line-options) - Leaves searchd in foreground
* [--ntservice](Starting_the_server/Manually.md#searchd-command-line-options) - Passed by Microsoft Management Console to searchd to invoke it as a service on Windows platforms
* [--pidfile](Starting_the_server/Manually.md#searchd-command-line-options) - Overrides [pid_file](Server_settings/Searchd.md#pid_file) from the configuration file
* [--port, p](Starting_the_server/Manually.md#searchd-command-line-options) - Specifies port searchd should listen on disregarding the port specified in the configuration file
* [--replay-flags](Starting_the_server/Manually.md#searchd-command-line-options) - Specifies extra binary log replay options
* [--servicename](Starting_the_server/Manually.md#searchd-command-line-options) - Applies the given name to searchd when installing or deleting the service, as would appear in Microsoft Management Console
* [--status](Starting_the_server/Manually.md#searchd-command-line-options) - Queries running search to return its status
* [--stop](Starting_the_server/Manually.md#searchd-command-line-options) - Stops Manticore server
* [--stopwait](Starting_the_server/Manually.md#searchd-command-line-options) - Stops Manticore server gracefully
* [--strip-path](Starting_the_server/Manually.md#searchd-command-line-options) - Strips path names from all the file names referenced from the table
* [-v](Starting_the_server/Manually.md#searchd-command-line-options) - shows version information

##### Searchd environment variables
* [MANTICORE_TRACK_DAEMON_SHUTDOWN](Starting_the_server/Manually.md#Environment-variables) - enables detailed logging while searchd is shutting down

## [Indextool](Miscellaneous_tools.md#indextool)
Miscellaneous table maintenance functionality useful for troubleshooting.
```bash
indextool <command> [options]
```
##### Indextool start parameters
Used to dump miscellaneous debug information about the physical table
```bash
indextool <command> [options]
```
* [--config, -c](Miscellaneous_tools.md#indextool) - Path to configuration file
* [--quiet, -q](Miscellaneous_tools.md#indextool) - Keeps indextool quiet - it will not output banner, etc
* [--help, -h](Miscellaneous_tools.md#indextool) - Lists all the parameters
* [-v](Miscellaneous_tools.md#indextool) - Shows version information
* [Indextool](Miscellaneous_tools.md#indextool) - Verifies configuration file
* [--buildidf](Miscellaneous_tools.md#indextool) - Builds IDF file from one or several dictionary dumps
* [--build-infixes](Miscellaneous_tools.md#indextool) - Build infixes for an existing dict=keywords table
* [--dumpheader](Miscellaneous_tools.md#indextool) - Quickly dumps the provided table header file
* [--dumpconfig](Miscellaneous_tools.md#indextool) - Dumps table definition from the given table header file in almost compliant manticore.conf file format
* [--dumpheader](Miscellaneous_tools.md#indextool) - Dumps table header by table name with looking up the header path in the configuration file
* [--dumpdict](Miscellaneous_tools.md#indextool) - Dumps table dictionary
* [--dumpdocids](Miscellaneous_tools.md#indextool) - Dumps document IDs by table name
* [--dumphitlist](Miscellaneous_tools.md#indextool) - Dumps all occurrences of the given keyword/id in the given table
* [--docextract](Miscellaneous_tools.md#indextool) - Runs table check pass of whole dictionary/docs/hits, and collects all the words and hits belonging to requested document
* [--fold](Miscellaneous_tools.md#indextool) - Tests tokenization based on table's settings
* [--htmlstrip](Miscellaneous_tools.md#indextool) - Filters STDIN using HTML stripper settings for the given table
* [--mergeidf](Miscellaneous_tools.md#indextool) - Merges several .idf files into a single one
* [--morph](Miscellaneous_tools.md#indextool) - Applies morphology to the given STDIN and prints the result to stdout
* [--check](Miscellaneous_tools.md#indextool) - Checks the table data files for consistency
* [--check-id-dups](Miscellaneous_tools.md#indextool) - Checks if there are duplicate ids
* [--check-disk-chunk](Miscellaneous_tools.md#indextool) - Checks one disk chunk of an RT table
* [--strip-path](Miscellaneous_tools.md#indextool) - Strips path names from all the file names referenced from the table
* [--rotate](Miscellaneous_tools.md#indextool) - Defines whether to check table waiting for rotation in `--check`
* [--apply-killlists](Miscellaneous_tools.md#indextool) - Applies kill-lists for all tables listed in the configuration file

## [Wordbreaker](Miscellaneous_tools.md#wordbreaker)
Splits compound words into components.
```bash
wordbreaker [-dict path/to/dictionary_file] {split|test|bench}
```

##### Wordbreaker start parameters.
* [STDIN](Miscellaneous_tools.md#wordbreaker) - To accept string to break into parts
* [-dict](Miscellaneous_tools.md#wordbreaker) - Specifies dictionary file to use
* [split|test|bench](Miscellaneous_tools.md#wordbreaker) - Specifies command

## [Spelldump](Miscellaneous_tools.md#spelldump)
Used to extract contents of a dictionary file that uses ispell or MySpell format.
```bash
spelldump [options] <dictionary> <affix> [result] [locale-name]
```
* [dictionary](Miscellaneous_tools.md#spelldump) - Dictionary's main file
* [affix](Miscellaneous_tools.md#spelldump) - Dictionary's affix file
* [result](Miscellaneous_tools.md#spelldump) - Specifies where the dictionary data should be output to
* [locale-name](Miscellaneous_tools.md#spelldump) - Specifies the locale details to use

## List of reserved keywords

A complete alphabetical list of keywords that are currently reserved in Manticore SQL syntax (and therefore can not be used as identifiers).

```
AND, AS, BY, COLUMNARSCAN, DISTINCT, DIV, DOCIDINDEX, EXPLAIN, FACET, FALSE, FORCE, FROM, IGNORE, IN, INDEXES, IS, LIMIT, MOD, NOT, NO_COLUMNARSCAN, NO_DOCIDINDEX, NO_OPTIMIZEFULLTEXTFILTERS, NO_SECONDARYINDEX, NULL, OFFSET, OPTIMIZEFULLTEXTFILTERS, OR, ORDER, REGEX, RELOAD, SECONDARYINDEX, SELECT, SYSFILTERS, TRUE, USE
```

## Documentation for old Manticore versions

* [2.4.1](https://repo.manticoresearch.com/repository/old_docs/manticoresearch-2.4.1.pdf)
* [2.5.1](https://repo.manticoresearch.com/repository/old_docs/manticoresearch-2.5.1.pdf)
* [2.6.0](https://repo.manticoresearch.com/repository/old_docs/manticoresearch-2.6.0.pdf)
* [2.6.1](https://repo.manticoresearch.com/repository/old_docs/manticoresearch-2.6.1.pdf)
* [2.6.2](https://repo.manticoresearch.com/repository/old_docs/manticoresearch-2.6.2.pdf)
* [2.6.3](https://repo.manticoresearch.com/repository/old_docs/manticoresearch-2.6.3.pdf)
* [2.6.4](https://repo.manticoresearch.com/repository/old_docs/manticoresearch-2.6.4.pdf)
* [2.7.0](https://repo.manticoresearch.com/repository/old_docs/manticoresearch-2.7.0.pdf)
* [2.7.1](https://repo.manticoresearch.com/repository/old_docs/manticoresearch-2.7.1.pdf)
* [2.7.2](https://repo.manticoresearch.com/repository/old_docs/manticoresearch-2.7.2.pdf)
* [2.7.3](https://repo.manticoresearch.com/repository/old_docs/manticoresearch-2.7.3.pdf)
* [2.7.4](https://repo.manticoresearch.com/repository/old_docs/manticoresearch-2.7.4.pdf)
* [2.7.5](https://repo.manticoresearch.com/repository/old_docs/manticoresearch-2.7.5.pdf)
* [2.8.0](https://repo.manticoresearch.com/repository/old_docs/manticoresearch-2.8.0.pdf)
* [2.8.1](https://repo.manticoresearch.com/repository/old_docs/manticoresearch-2.8.1.pdf)
* [2.8.2](https://repo.manticoresearch.com/repository/old_docs/manticoresearch-2.8.2.pdf)
* [3.0.0](https://repo.manticoresearch.com/repository/old_docs/manticoresearch-3.0.0.pdf)
* [3.0.2](https://repo.manticoresearch.com/repository/old_docs/manticoresearch-3.0.2.pdf)
* [3.1.0](https://repo.manticoresearch.com/repository/old_docs/manticoresearch-3.1.0.pdf)
* [3.1.2](https://repo.manticoresearch.com/repository/old_docs/manticoresearch-3.1.2.pdf)
* [3.2.0](https://repo.manticoresearch.com/repository/old_docs/manticoresearch-3.2.0.pdf)
* [3.2.2](https://repo.manticoresearch.com/repository/old_docs/manticoresearch-3.2.2.pdf)
* [3.3.0](https://repo.manticoresearch.com/repository/old_docs/manticoresearch-3.3.0.pdf)
* [3.4.0](https://repo.manticoresearch.com/repository/old_docs/manticoresearch-3.4.0.pdf)
* [3.4.2](https://repo.manticoresearch.com/repository/old_docs/manticoresearch-3.4.2.pdf)
* [3.5.0](https://manual.manticoresearch.com/manticore-3-5-0/)
* [3.5.2](https://manual.manticoresearch.com/manticore-3-5-2/)
* [3.5.4](https://manual.manticoresearch.com/manticore-3-5-4/)
* [3.6.0](https://manual.manticoresearch.com/manticore-3-6-0/)
* [4.0.2](https://manual.manticoresearch.com/manticore-4-0-2/)
* [4.2.0](https://manual.manticoresearch.com/manticore-4-2-0/)
