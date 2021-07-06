#include <NTL/ZZ.h>
#include <iostream>
#include "headers/RSA.h"
#include "headers/functions.h"
#include <vector>

using std::cin;
using std::cout;
using std::endl;

int main()
{

    ZZ bits, p, q, e, ea, Na, eb, Nb;
    bool WithSig;
    vector<string>Cypher;
    vector<string>DCypher;
    string alpha, sig, message;

    bits = 1024;
    alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ,.-( )abcdefghijklmnopqrstuvwxyz<>*1234567890[]";
    sig = "Sebastian Tinajeros Estrada Sebastian Gonzalo Postigo Avalos Fabian Concha Sifuentes Joaquin Casusol Escalante Frank Salas Ticona 201-10-47883 201-10-48100 201-10-47533 201-10-47494 201-10-47829 sebastian.tinajerosucsp.edu.pe sebastian.postigoucsp.edu.pe fabian.conchaucsp.edu.pe joaquin.casusolucsp.edu.pe frank.salasucsp.edu.pe";
    message="The idea of an asymmetric public-private key cryptosystem is attributed to Whitfield Diffie and Martin Hellman, who published this concept in 1976. They also introduced digital signatures and attempted to apply number theory. Their formulation used a shared-secret-key created from exponentiation of some number, modulo a prime number. However, they left open the problem of realizing a one-way function, possibly because the difficulty of factoring was not well-studied at the time.[4] Ron Rivest, Adi Shamir, and Leonard Adleman at the Massachusetts Institute of Technology, made several attempts over the course of a year to create a one-way function that was hard to invert. Rivest and Shamir, as computer scientists, proposed many potential functions, while Adleman, as a mathematician, was responsible for finding their weaknesses. They tried many approaches including knapsack-based and permutation polynomials. For a time, they thought what they wanted to achieve was impossible due to contradictory requirements.[5] In April 1977, they spent Passover at the house of a student and drank a good deal of Manischewitz wine before returning to their homes at around midnight.[6] Rivest, unable to sleep, lay on the couch with a math textbook and started thinking about their one-way function. He spent the rest of the night formalizing his idea, and he had much of the paper ready by daybreak. The algorithm is now known as RSA the initials of their surnames in same order as their paper.[7] Clifford Cocks, an English mathematician working for the British intelligence agency Government Communications Headquarters (GCHQ), described an equivalent system in an internal document in 1973.[8] However, given the relatively expensive computers needed to implement it at the time, it was considered to be mostly a curiosity and, as far as is publicly known, was never deployed. His discovery, however, was not revealed until 1997 due to its top-secret classification. Kid-RSA (KRSA) is a simplified public-key cipher published in 1997, designed for educational purposes. Some people feel that learning Kid-RSA gives insight into RSA and other public-key ciphers, analogous to simplified DES.[9][10][11][12][13] A patent describing the RSA algorithm was granted to MIT on 20 September 1983 U.S. Patent 4,405,829 Cryptographic communications system and method. From DWPIs abstract of the patent The system includes a communications channel coupled to at least one terminal having an encoding device and to at least one terminal having a decoding device. A message-to-be-transferred is enciphered to ciphertext at the encoding terminal by encoding the message as a number M in a predetermined set. That number is then raised to a first predetermined power (associated with the intended receiver) and finally computed. The remainder or residue, C, is... computed when the exponentiated number is divided by the product of two predetermined prime numbers (associated with the intended receiver). A detailed description of the algorithm was published in August 1977, in Scientific Americans Mathematical Games column.[7] This preceded the patents filing date of December 1977. Consequently, the patent had no legal standing outside the United States. Had Cockss work been publicly known, a patent in the United States would not have been legal either. When the patent was issued, terms of patent were 17 years. The patent was about to expire, on 21 September 2000, when RSA Security released the algorithm to the public domain, on 6 September 2000.[14] There are a number of attacks against plain RSA as described below.When encrypting with low encryption exponents (e.g., e  3) and small values of the m, (i.e., m <n1e) the result of me is strictly less than the modulus n. In this case, ciphertexts can be decrypted easily by taking the eth root of the ciphertext over the integers. If the same clear text message is sent to e or more recipients in an encrypted way, and the receivers share the same exponent e, but different p, q, and therefore n, then it is easy to decrypt the original clear text message via the Chinese remainder theorem. Johan Hstad noticed that this attack is possible even if the cleartexts are not equal, but the attacker knows a linear relation between them.[22] This attack was later improved by Don Coppersmith (see Coppersmiths attack).[23] Because RSA encryption is a deterministic encryption algorithm (i.e., has no random component) an attacker can successfully launch a chosen plaintext attack against the cryptosystem, by encrypting likely plaintexts under the public key and test if they are equal to the ciphertext. A cryptosystem is called semantically secure if an attacker cannot distinguish two encryptions from each other, even if the attacker knows (or has chosen) the corresponding plaintexts. As described above, RSA without padding is not semantically secure.[24] RSA has the property that the product of two ciphertexts is equal to the encryption of the product of the respective plaintexts. That is m1em2e  (m1m2)e (mod n). Because of this multiplicative property a chosen-ciphertext attack is possible. E.g., an attacker who wants to know the decryption of a ciphertext c  me (mod n) may ask the holder of the private key d to decrypt an unsuspicious-looking ciphertext c  cre (mod n) for some value r chosen by the attacker. Because of the multiplicative property c is the encryption of mr (mod n). Hence, if the attacker is successful with the attack, they will learn mr (mod n) from which they can derive the message m by multiplying mr with the modular inverse of r modulo n.[citation needed] Given the private exponent d one can efficiently factor the modulus n  pq. And given factorization of the modulus n  pq, one can obtain any private key (d,n) generated against a public key (e,n).[15] To avoid these problems, practical RSA implementations typically embed some form of structured, randomized padding into the value m before encrypting it. This padding ensures that m does not fall into the range of insecure plaintexts, and that a given message, once padded, will encrypt to one of a large number of different possible ciphertexts. Standards such as PKCS1 have been carefully designed to securely pad messages prior to RSA encryption. Because these schemes pad the plaintext m with some number of additional bits, the size of the un-padded message M must be somewhat smaller. RSA padding schemes must be carefully designed so as to prevent sophisticated attacks that may be facilitated by a predictable message structure. Early versions of the PKCS1 standard (up to version 1.5) used a construction that appears to make RSA semantically secure. However, at Crypto 1998, Bleichenbacher showed that this version is vulnerable to a practical adaptive chosen ciphertext attack. Furthermore, at Eurocrypt 2000, Coron et al.[25] showed that for some types of messages, this padding does not provide a high enough level of security. Later versions of the standard include Optimal Asymmetric Encryption Padding (OAEP), which prevents these attacks. As such, OAEP should be used in any new application, and PKCS1 v1.5 padding should be replaced wherever possible. The PKCS1 standard also incorporates processing schemes designed to provide additional security for RSA signatures, e.g. the Probabilistic fSignature Scheme for RSA (RSA-PSS). Secure padding schemes such as RSA-PSS are as essential for the security of message signing as they are for message encryption. Two USA patents on PSS were granted (USPTO 6266771 and USPTO 70360140) however, these patents expired on 24 July 2009 and 25 April 2010, respectively. Use of PSS no longer seems to be encumbered by patents.[original research] Note that using different RSA key-pairs for encryption and signing is potentially more secure.[26]";

    char input;
    std::cout<<"RSA";
    std::cout<<"\nPara Test completo (a), para Generar numeros (b), Para cifrar o descifrar(c)\n";
    std::cin>>input;

    if (input=='a'){
        std::cout<<"\nTEST COMPLETO\n";
        //nuestro abecedario y firma
        std::cout<<"\nEMISOR:\n";
        RSA Emisor(bits,alpha,sig);
        std::cout<<"\nRECEPTOR:\n";
        RSA Receptor(bits,alpha,sig);

        //claves publicas
        ea = Emisor.e;
        Na = Emisor.N;
        eb = Receptor.e;
        Nb = Receptor.N;
        WithSig = true;
        //Emisor cifra
        vector<string>Cypher = Emisor.cypherwithsignature(message, eb, Nb);
        cout << "El mensajeCifrado es: \n" << Cypher.at(0) << "\nfirma:\n" << Cypher.at(1) << endl;
        //Receptor decifra
        vector<string>DCypher = Receptor.decypherwithsignature(Cypher, ea, Na);
        cout << "\nMensaje:\n" << DCypher.at(0) << "\nfirma\n" << DCypher.at(1) << endl;
    }
//GENERADOR DE NUMEROS

    else if (input=='b'){
        std::cout<<"\nGENERANDO NUMEROS...\n";
        RSA generator(bits,alpha,sig);
    }

//CIFRANDO Y DECIFRANDO

    else if (input=='c'){
        std::cout<<"\nCifrado o descifrado\n";
        p = conv<ZZ>("87221499727435745364535332112490969356263865649831513472029650441094546380074558974832871619761129229532353687983721800525130932582745432833068981993612899087013491494396714879741604694978092825295888935435059622998421240882102073123565616688155539117083007531183964194648709145338857769194325488901853148787");
        q = conv<ZZ>("60445924003714535319529895405889617954056355433186960882336333498478465261659054610858115656794335453396985208004529511344016403763741806583226061008579353366652388699478864306419142179324087848055434075831589235885497525037769865186483889463925409830291601620238380152087586858209913131391943415417598612287");
        e = conv<ZZ>("102990113052606600626911910675349554419313652275024968208595635572346469121621367631476552882178281241345115406769958859872126794148933238543313855371481693751760418978360830158281221748455177885510428967023975711141900865431930521476529661789318095627416160928482680191608493935991041876685945701000607170559");

        RSA testing(p, q, e, alpha, sig);

        eb=conv<ZZ>("144121440877962064075053496035105812687954153106964832795611266023012228294266419920387047570032091979209579438355582130486569076199273864468671454435545529423088492518902407707650347983580988222322037231033997314613026669478910475493530245814694228551543719454763403186750631415314022248891452099219838389633");
        Nb=conv<ZZ>("16289910449813943591906591709595252023079852543601245472904204095442647497952106458266527322251529739312528001827461352406522517110665543801764343554457996834209343448122637484473073045715865217445993071499611292035841667767051803145357632791437632564455633936921110995339707022395368357479759073738913754631457108353146853138307039644889937240114239423492312593150281848636224894620362507135120610265627126368872348654232379889626286524893256969270937846554783343630498460256240761683838701223222673045851024260322795364109998360892393301933022513429202489556299523222740577430303202425196179087887677362763904115461");
        std::cout<<"\nCLAVES PUBLICAS DE RECEPTOR\ne: "<<eb<<"\nN: "<<Nb<<"\n";
        std::cout<<"\nPara cifrar(a), para descifrar(b)\n";
        std::cin>>input;
        if (input=='a'){
            //CIFRADO
            std::cout<<"\nCifrando...\n";
            //mensaje
            Cypher=testing.cypherwithsignature(message,eb,Nb);
            std::cout<<"\nMessage: \n"<<Cypher.at(0)<<"\nSignature: \n"<<Cypher.at(1);
        }
        else if (input=='b'){
            //DECIFRADO
            std::cout<<"\nDescifrando...\n";
            //mensaje
            DCypher.push_back("36003872863126113930851552674551878575889041263062757242697751963926392072346059021655931041494193099973566818489081694226779133325860549677881808050661153395639433801004206540682144937414023273112231540720349590470694896667492538598997564662276247092188548933421161559120281295581848434415879058095305891884268294508083329396724631968235085875051219947796295952229957457288598652230914302507960921437539660313181198754489764721797766884737118131831742021912673271438653357804552095173357793899021128892936180870340847536675163229781648004333352763818761663579613376335892456166241759959887350344966800138389988569194052742480799425282890396941063789467758115669196808226311337424628380413078575684602434730387166261917583489187169476684876947310887580549078353479060172481505732317679372332869239717953114653189617937952721890430240484290620450169150834520338436921002954815257941722881250498674183586643116894767701040220669263713442308581999095113641398233696550390561603816261469624176793482394769099065477833924302001784574145615628648637768358569278503752809857075455609594996808470204336368498051026456760538385282939413906405245436422262233149993667526952351726575170420598544359655527930927581115777793792932596054138265219");
            //firma
            DCypher.push_back("28677100005993588582572858853266377738104753899340251602596243066994079129589825345253759511595132632765583542611274308091352033990425752064081222822916537247307822165357736943839618756072515766654744350498274836504352769835740363241730484459086545674455345342262769541791889148630002727751742350532780021371298672069884673708836702087558266724373456757309724126810063459153425055640658672498568971325543827392998827318318026200023986163766210023264711843231389259303750973820489100542834298083382680025304854177735399106121418619251213492907010422240684078688664832861090659348355300387548281918526928405741754990291377456681278587692262827880404560298844302015770335463786032596903138719385996113152881541006872331305385699911589052216408549841938749660888035074232883943951539936109428644048870332349084274776616955471039045247827979154464770353125623652746015877861281472923338010625697060590985732792705381153262897531472554141032607062173106184926173234877707246379332373446749324407262553259048596470018227874379724848156580391081902842940605514871073587281302330676376641482211394024669985002163105657851813497146178411632763665957023375566211262428026050555479397873186165089798229340031549902562289251953694342303327401927381978657637224690880875071334560702838756070344560197332439042108633968766279277441372419918029288966770561858662899982922347646583568624372950512562506265238270254822826303692828191205772065019248312346904359909371548244775542802638096690708191255069336864116140337250447860983770334678937577592057408534761988073187450637226880794246098345558744175670436500065278945353588042212410968628599579774290480242311863578302898047863003862743607571689505637797586357882522965352488603061791788103653524283274193966560073539650345715592224252406337533914247445100811201129455647961465770509999954261444070581838161432823911834572149073505507869332458408610063090835402461831301227147267794922219372055572968833956250973846681279694064321697921456423394031510373329973832166791822451454816182989470048450973991431000754152083873443227316139428026897482987162511456211736691350848542337005272714572826508423593132944155992103020804922486540422196666855305154907665596856115575345281026466372805974487185064566004007235477557225352654979830712859270810302453278992227880191849556184066686398725375666863116667096666684168762525168656510430462634693655631027969984553951250894744643911262738858627800169669637195069351687500339822618105419865076243142964741617390686917065315152786091985441087895582843390425954200150408352614165610124987883358026985615110841511841904402855848253800089700789209426359834903162380940042976154243224760445793553650816079476329458270499794074627781669068201605810528784356100859714921349151649835089578037889574762588307446914843558138083145943241808422501778380981141391375071935493150230166992731730037367592186183828268211593535680062222729364318822064334130282838096325764041239191994559650614501304790160032982221831079663212634247014981777292374303585397173680299980689360515737168139023838105898153806156683355888368040");
            DCypher=testing.decypherwithsignature(DCypher,eb,Nb);
            std::cout<<"\nMensaje:\n"<<DCypher.at(0)<<"\nFirma:\n"<<DCypher.at(1);
        }
    }
}
