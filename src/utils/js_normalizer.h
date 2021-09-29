//--------------------------------------------------------------------------
// Copyright (C) 2021-2021 Cisco and/or its affiliates. All rights reserved.
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License Version 2 as published
// by the Free Software Foundation.  You may not use, modify or distribute
// this program under any other version of the GNU General Public License.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//--------------------------------------------------------------------------
// js_normalizer.h author Oleksandr Serhiienko <oserhiie@cisco.com>

#ifndef JS_NORMALIZER_H
#define JS_NORMALIZER_H

#include "main/snort_types.h"

#include <FlexLexer.h>

#include "js_tokenizer.h"
#include "streambuf.h"

namespace snort
{

class JSNormalizer
{
public:
    JSNormalizer(JSIdentifierCtxBase& js_ident_ctx, size_t depth,
        uint8_t max_template_nesting, int tmp_cap_size = JSTOKENIZER_BUF_MAX_SIZE);
    ~JSNormalizer();

    const char* get_src_next() const
    { return src_next; }

    void reset_depth()
    { rem_bytes = depth; }

    JSTokenizer::JSRet normalize(const char* src, size_t src_len);
    std::pair<char*,size_t> get_script();
    size_t peek_script_size();
    void prepend_script(const void*, size_t);

    static size_t size();

#ifdef BENCHMARK_TEST
    void rewind_output();
#endif

private:
    size_t depth;
    size_t rem_bytes;
    bool unlim;
    const char* src_next;

    char* tmp_buf;
    size_t tmp_buf_size;

    istreambuf_glue in_buf;
    ostreambuf_infl out_buf;
    std::istream in;
    std::ostream out;
    JSTokenizer tokenizer;
};

}

#endif //JS_NORMALIZER_H
