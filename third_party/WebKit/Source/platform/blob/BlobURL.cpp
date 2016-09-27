/*
 * Copyright (C) 2010 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "platform/blob/BlobURL.h"

#include "platform/UUID.h"
#include "platform/weborigin/KURL.h"
#include "platform/weborigin/SecurityOrigin.h"
#include "wtf/text/WTFString.h"

namespace blink {

const char BlobURL::kBlobProtocol[] = "blob";

KURL BlobURL::createPublicURL(SecurityOrigin* securityOrigin)
{
    ASSERT(securityOrigin);
    return createBlobURL(securityOrigin->toString());
}

String BlobURL::getOrigin(const KURL& url)
{
    ASSERT(url.protocolIs(kBlobProtocol));

    unsigned startIndex = url.pathStart();
    unsigned endIndex = url.pathAfterLastSlash();
    return url.string().substring(startIndex, endIndex - startIndex - 1);
}

KURL BlobURL::createInternalStreamURL()
{
    return createBlobURL("blobinternal://");
}

KURL BlobURL::createBlobURL(const String& originString)
{
    ASSERT(!originString.isEmpty());
    String urlString = "blob:" + encodeWithURLEscapeSequences(originString) + '/' + createCanonicalUUIDString();
#ifdef MINIBLINK_NOT_IMPLEMENTED
    return KURL::createIsolated(ParsedURLString, urlString);
#endif // MINIBLINK_NOT_IMPLEMENTED
	notImplemented();
	return KURL();
}

} // namespace blink