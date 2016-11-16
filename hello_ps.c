#include <pocketsphinx.h>
#include <iostream>

#define write
int main(int argc, char *argv[]){

        ps_decoder_t *ps = NULL;
        cmd_ln_t *config = NULL;
        FILE *file = NULL;
        char const *hyp, *uttid;
        int16 buff[512];
        int rv;
        int32 score;

        config = cmd_ln_init(NULL, ps_args(), TRUE,
                 "-hmm", MODELDIR "/en-us/en-us",
                 "-lm", MODELDIR "/en-us/en-us.lm.bin",
                 "-dict", MODELDIR "/en-us/cmudict-en-us.dict",
                 NULL);
        if (config == NULL){
	std::cout << "Failed to create config object." 
	<< " At line: " << __LINE__ << std::endl;        	
	return -1;
        }

        ps = ps_init(config)
        if (ps == NULL){
        	std::cout << "Failed to create recognizer object." 
	<< " At line: " <<  __LINE__ << std::endl;        	
	return -1;
        }

        file = fopen("goforward.raw", "rb");
        if (file == NULL){
        	std::cout << "Failed to read/find file." 
	<< " At line: " <<  __LINE__ << std::endl;        	
	return -1;
        }

        rv = ps_start_utt(ps);

        while(!feof(file)){
        	size_t nsamp;
        	nsamp = fread(buff, 2, 512, file);
        	rv = ps_process_raw(ps, buff, nsamp, FALSE, FALSE);
        }

        rv = ps_end_utt(ps)
        hyp = ps_get_hyp(ps, &score);
        std::cout << "Recognized: " << hyp << std::endl;

        fclose(fh);
        ps_free(ps);
        cmd_ln_free_r(config);

        return 0;
}


