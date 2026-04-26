/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "sql/executor/drop_table_executor.h"
#include "sql/stmt/drop_table_stmt.h"
#include "event/sql_event.h"
#include "event/session_event.h"
#include "session/session.h"
#include "storage/db/db.h"
#include "common/log/log.h"

RC DropTableExecutor::execute(SQLStageEvent *sql_event)
{
    if (sql_event == nullptr) {
        return RC::INVALID_ARGUMENT;
    }

    Stmt *stmt = sql_event->stmt();
    if (stmt == nullptr) {
        return RC::INVALID_ARGUMENT;
    }

    DropTableStmt *drop_stmt = static_cast<DropTableStmt *>(stmt);
    
    SessionEvent *session_event = sql_event->session_event();
    if (session_event == nullptr) {
        return RC::INVALID_ARGUMENT;
    }
    
    Session *session = session_event->session();
    if (session == nullptr) {
        return RC::INVALID_ARGUMENT;
    }

    Db *db = session->get_current_db();
    if (db == nullptr) {
        LOG_WARN("no database selected, please use a database first");
        return RC::INVALID_ARGUMENT;
    }
    
    const std::string &table_name = drop_stmt->table_name();
    LOG_INFO("executing drop table: %s", table_name.c_str());
    
    return db->drop_table(table_name.c_str());
}