#ifndef __J_CC_MACRO_H__
#define __J_CC_MACRO_H__

#define PARMSG(tok, tp, fmt, ...) parmsg(job, tok, tp, fmt, ##__VA_ARGS__)
#define PREPMSG(tok, tp, fmt, ...) prepmsg(*m_job, tok, tp, fmt, ##__VA_ARGS__)

#define JCC_INTERNAL

#endif // __J_CC_MACRO_H__