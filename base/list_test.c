#include "list.h"
#include "str.h"
#include <stdio.h>

const char* test_sdp=
"v=0\n"
"o=- 3546004397921447048 1596742744 IN IP4 0.0.0.0\n"
"s=-\n"
"t=0 0\n"
"a=fingerprint:sha-256 0F:74:31:25:CB:A2:13:EC:28:6F:6D:2C:61:FF:5D:C2:BC:B9:DB:3D:98:14:8D:1A:BB:EA:33:0C:A4:60:A8:8E\n"
"a=group:BUNDLE 0 1\n"
"m=audio 9 UDP/TLS/RTP/SAVPF 111\n"
"c=IN IP4 0.0.0.0\n"
"a=setup:active\n"
"a=mid:0\n"
"a=ice-ufrag:CsxzEWmoKpJyscFj\n"
"a=ice-pwd:mktpbhgREmjEwUFSIJyPINPUhgDqJlSd\n"
"a=rtcp-mux\n"
"a=rtcp-rsize\n"
"a=rtpmap:111 opus/48000/2\n"
"a=fmtp:111 minptime=10;useinbandfec=1\n"
"a=ssrc:350842737 cname:yvKPspsHcYcwGFTw\n"
"a=ssrc:350842737 msid:yvKPspsHcYcwGFTw DfQnKjQQuwceLFdV\n"
"a=ssrc:350842737 mslabel:yvKPspsHcYcwGFTw\n"
"a=ssrc:350842737 label:DfQnKjQQuwceLFdV\n"
"a=msid:yvKPspsHcYcwGFTw DfQnKjQQuwceLFdV\n"
"a=sendrecv\n"
"a=candidate:foundation 1 udp 2130706431 192.168.1.1 53165 typ host generation 0\n"
"a=candidate:foundation 2 udp 2130706431 192.168.1.1 53165 typ host generation 0\n"
"a=candidate:foundation 1 udp 1694498815 1.2.3.4 57336 typ srflx raddr 0.0.0.0 rport 57336 generation 0\n"
"a=candidate:foundation 2 udp 1694498815 1.2.3.4 57336 typ srflx raddr 0.0.0.0 rport 57336 generation 0\n"
"a=end-of-candidates\n"
"m=video 9 UDP/TLS/RTP/SAVPF 96\n"
"c=IN IP4 0.0.0.0\n"
"a=setup:active\n"
"a=mid:1\n"
"a=ice-ufrag:CsxzEWmoKpJyscFj\n"
"a=ice-pwd:mktpbhgREmjEwUFSIJyPINPUhgDqJlSd\n"
"a=rtcp-mux\n"
"a=rtcp-rsize\n"
"a=rtpmap:96 VP8/90000\n"
"a=ssrc:2180035812 cname:XHbOTNRFnLtesHwJ\n"
"a=ssrc:2180035812 msid:XHbOTNRFnLtesHwJ JgtwEhBWNEiOnhuW\n"
"a=ssrc:2180035812 mslabel:XHbOTNRFnLtesHwJ\n"
"a=ssrc:2180035812 label:JgtwEhBWNEiOnhuW\n"
"a=msid:XHbOTNRFnLtesHwJ JgtwEhBWNEiOnhuW\n"
"a=sendrecv\n";

int main(){

    lc_str *str = lc_str_create(test_sdp);

    lc_vector* v = lc_str_split_char(str, '\n');

    lc_list *l = lc_list_create(NULL, NULL);

    for(int i = 0;  i < v->size; i ++){
        lc_str* tmp = lc_vector_get(v, i);
        lc_list_add(l, tmp);
    }

    int i = 0;
    lc_list_foreach(l, e){
        lc_str* l_str = e->data;
        lc_str* v_str = lc_vector_get(v, i);
        if(l_str != v_str){
            printf("error \n");
        }
        printf("%s\n",l_str->c_str);
        i++;
    }

    lc_list_destroy(l);
    lc_vector_destroy(v);
    lc_str_destroy(str);
    return 0;
}
