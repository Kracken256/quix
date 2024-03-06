# Build me with quixcc -o myname.so interactive-build.q -shared -s
# The name you type will be stored in the shared object file in a symbol named `_ZJ0l16DEVELOPERS__NAME1s0` as a c-string

@print info "I am the QUIX macro engine"
@print info "I can read and write like a real boy"
@print warn "I am powerful, yet elegant"
@print info "You can speak to me in binary or your native tongue"
@print raw "What's your name mortal? "

pub let DEVELOPERS_NAME: string = @(readstdin 30);
@print raw "Hi bro.\n"
@print info "In the future, Ill be able to talk to the internet and do all sorts of cool stuff"
@print info "How about compile time API key validation? Or even generate 50MB of test cases on demand?"
@print good "I am the future of programming"

pub fn _start() {
    @print warn "Love me or hate me, but if it's the later, you must be assimilated!"
}