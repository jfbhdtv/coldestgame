#include "StableRandom.h"

float StableRandom::vals[] = {0.3979798083, 0.483040806351, 0.0371909144495, 0.972458231571, 0.232765731613, 0.167247892145, 0.506537465507, 0.539061716029, 0.978512595459, 0.3981065523, 0.942519136403, 0.113496395086, 0.897034640667, 0.80046314, 0.390278323594, 0.0437815911637, 0.737004589753, 0.313193848582, 0.76682337006, 0.366950402768, 0.787976209162, 0.990487658047, 0.519941097196, 0.499961503132, 0.651982835105, 0.307155202792, 0.670081406619, 0.943225876559, 0.833656724046, 0.364012375682, 0.923746682166, 0.470915445517, 0.386366809497, 0.71395435401, 0.590916585608, 0.794911771607, 0.881173994172, 0.145207573756, 0.393814882193, 0.395620166001, 0.977293767257, 0.0326306975646, 0.864167564372, 0.923550760583, 0.997869915836, 0.343477565925, 0.579781796201, 0.81770615446, 0.293252817665, 0.235097439738, 0.0150867847151, 0.366446073662, 0.213481709387, 0.81169861221, 0.771245424994, 0.509559710146, 0.885320644735, 0.824838467426, 0.393531759692, 0.898258823692, 0.836031020932, 0.585225539444, 0.793631675109, 0.263565112141, 0.390202405764, 0.923546497736, 0.459412840525, 0.983451073823, 0.682872431718, 0.573380987071, 0.0939461927241, 0.147890616388, 0.81456195234, 0.418824931408, 0.915246603058, 0.0590776938446, 0.279295574371, 0.864561643758, 0.409859390301, 0.5561733981, 0.420617798935, 0.394360465943, 0.452138424181, 0.399366758982, 0.668754912993, 0.923365799361, 0.150206263265, 0.876565706636, 0.500622620106, 0.169740170614, 0.579612829692, 0.366811500293, 0.268382467525, 0.666462466678, 0.0754050439935, 0.709553635615, 0.333466131742, 0.0241361809478, 0.597915810731, 0.834405594724, 0.0599135364609, 0.496352975004, 0.51937571465, 0.963196723525, 0.480467483498, 0.915122124481, 0.991305148391, 0.245326913355, 0.251837206951, 0.713731293865, 0.787650095291, 0.0248242328473, 0.174836190341, 0.0217380391104, 0.245012368811, 0.95018354641, 0.628782882324, 0.0640184004863, 0.632665033233, 0.465984047845, 0.91817257118, 0.857603124852, 0.912201379511, 0.645877344754, 0.747531561029, 0.629957009665, 0.879023388892, 0.212215019015, 0.625560004745, 0.329027126553, 0.128960721311, 0.273010339881, 0.815888322575, 0.199600907439, 0.458465822039, 0.875012845401, 0.841084862154, 0.590144412463, 0.501616926091, 0.542368606307, 0.930843523034, 0.321255137859, 0.910439473766, 0.452978791821, 0.731913791493, 0.639883222248, 0.946844604937, 0.97543584994, 0.866342115775, 0.943699495472, 0.0505869403563, 0.994555529782, 0.837467614056, 0.412098380593, 0.170167933172, 0.641647148174, 0.0880377542276, 0.996956469453, 0.522386267567, 0.394423786339, 0.678371503767, 0.726802516439, 0.762911618729, 0.367749867552, 0.192788753863, 0.927294486639, 0.515138234499, 0.411786916635, 0.64634709891, 0.116771877328, 0.796156933723, 0.371036337905, 0.0504036506011, 0.560011741963, 0.443434165899, 0.287918982419, 0.107245593351, 0.835436804412, 0.227662832563, 0.454220136916, 0.859781553878, 0.699987597323, 0.697852566327, 0.464724026619, 0.170438201155, 0.430380050481, 0.656412096663, 0.548354837145, 0.583307768926, 0.164784433864, 0.302459193589, 0.299750825329, 0.194105628678, 0.0939199796717, 0.685552113371, 0.403018322263, 0.715285391516, 0.790495277959, 0.493714382528, 0.595366512869, 0.463026943278, 0.945866040827, 0.133641522433, 0.863097554412, 0.144194185483, 0.905834529243, 0.10877151252, 0.756701650758, 0.566660952854, 0.790004558333, 0.805729810283, 0.403552025124, 0.512223986832, 0.599127013, 0.92958049958, 0.0174740434996, 0.379996872233, 0.654006046591, 0.794203816595, 0.562320584117, 0.628910488074, 0.820516907858, 0.425046560851, 0.307702995283, 0.243704015653, 0.136335821432, 0.747652163606, 0.34956026636, 0.0203674448962, 0.915816007958, 0.781053948684, 0.606224084316, 0.0527745837662, 0.181396285545, 0.0240967488173, 0.891686315936, 0.0765265335537, 0.427365219609, 0.39412385511, 0.456025858185, 0.895433385545, 0.931240063324, 0.915249484202, 0.785054897654, 0.942761226126, 0.826508210955, 0.331017547703, 0.866055220586, 0.019132965568, 0.783122645756, 0.102290856926, 0.681539595332, 0.644620578824, 0.251782394325, 0.812232809493, 0.912249786127, 0.527215943697, 0.0436861246088, 0.105257966596, 0.103280895306, 0.94763076887, 0.31642385806, 0.566968112683, 0.324806593427, 0.6232267683, 0.513793625417, 0.949544631755, 0.0572002802577, 0.94327881197, 0.989605659945, 0.673269710003, 0.203579920004, 0.64877317744, 0.845301609326, 0.702872010158, 0.575908782669, 0.986151189383, 0.863282699569, 0.615084196272, 0.0806581846578, 0.11788712295, 0.908547482375, 0.563407891538, 0.874624060216, 0.659649964718, 0.56519668367, 0.126986220018, 0.112045066285, 0.102384764782, 0.429035710347, 0.721572365822, 0.0639392047392, 0.29699114654, 0.618722811005, 0.0618649324455, 0.30239149045, 0.591930869282, 0.519429005377, 0.279236755802, 0.567956743287, 0.255302000401, 0.324193652662, 0.0120459527561, 0.883091916552, 0.277844199686, 0.415108786766, 0.356901280034, 0.997830737772, 0.574279148143, 0.0524670545227, 0.307405788341, 0.518759256842, 0.182587312428, 0.908608892242, 0.832622903777, 0.68852066791, 0.161207101097, 0.490509878383, 0.50539879723, 0.363176670629, 0.728393002665, 0.617560298912, 0.0399545775231, 0.356113443972, 0.22320724719, 0.704395269255, 0.177717442131, 0.32373201726, 0.263045972899, 0.9692763438, 0.286047411575, 0.434310111011, 0.537724049982, 0.759685391091, 0.498054278014, 0.928979105323, 0.235609354802, 0.702955191315, 0.0108877860853, 0.977906018351, 0.527670986711, 0.473102735591, 0.464917227387, 0.696808483591, 0.153377293881, 0.097804589739, 0.026289936634, 0.124551011309, 0.141228089661, 0.0121757759084, 0.201150177532, 0.975097890617, 0.18234085521, 0.841109081572, 0.0837445046132, 0.750289058568, 0.779279698275, 0.628051305549, 0.167024163363, 0.655429481799, 0.532494799164, 0.375078333324, 0.272789919048, 0.220932482636, 0.600861749314, 0.734653281026, 0.86660871765, 0.551943622759, 0.417940407585, 0.0694252688257, 0.946562479006, 0.223374099314, 0.600906108574, 0.975542305786, 0.563770147991, 0.582143604544, 0.712577423159, 0.829366071058, 0.954588377619, 0.477490579328, 0.677386195275, 0.147978533947, 0.0935886165834, 0.138879580517, 0.445466128481, 0.18130989834, 0.920767158624, 0.243359613124, 0.507270203888, 0.815542223561, 0.917315727423, 0.857754957033, 0.783000749116, 0.935911782597, 0.137426443515, 0.937271741338, 0.510666808506, 0.600085201595, 0.988939724694, 0.964924257418, 0.00832556704194, 0.949839039687, 0.602293362239, 0.180968780891, 0.152090517296, 0.409133649876, 0.657647320114, 0.163961661541, 0.161916912959, 0.164655233097, 0.750238503597, 0.745049696529, 0.422401170566, 0.336753641967, 0.176994059303, 0.984958686087, 0.131853941577, 0.229352689689, 0.0491664928514, 0.827490688728, 0.217601415571, 0.501880847418, 0.78165260903, 0.897064095478, 0.851830629017, 0.0894895912528, 0.375669392568, 0.0285024957338, 0.586852742174, 0.437993315937, 0.695519337326, 0.939244743457, 0.0415696732247, 0.397182054979, 0.649889770912, 0.309715510903, 0.0513714788913, 0.271925746872, 0.542779612337, 0.741937054994, 0.601691989087, 0.230627034887, 0.745778048034, 0.178269865471, 0.564704678143, 0.568097712903, 0.243960643949, 0.342974601889, 0.165009737585, 0.206503295978, 0.736185631746, 0.227279289905, 0.140863035267, 0.758873829621, 0.231861214824, 0.937795164771, 0.579520489168, 0.513192977766, 0.321948236508, 0.919788026974, 0.255070298763, 0.798189256415, 0.207830653286, 0.0391059367373, 0.0410417266292, 0.3233892948, 0.130320740653, 0.622396848403, 0.93638847238, 0.178553696576, 0.870333841908, 0.20866318469, 0.218669414889, 0.172847894882, 0.129779067347, 0.248709553166, 0.303329640651, 0.0768984130344, 0.706164184987, 0.774762992973, 0.644825283899, 0.0480974052541, 0.71886194266, 0.201669225899, 0.116288907833, 0.402619986463, 0.825344416979, 0.135743262437, 0.553196860049, 0.69971197835, 0.560720878669, 0.175694835594, 0.604822580158, 0.513669601936, 0.481226363407, 0.39182644227, 0.711640498477, 0.692190696522, 0.447093244497, 0.302398068234, 0.104499874082, 0.604179472453, 0.362185753718, 0.67221130897, 0.324656859876, 0.568249736001, 0.318323424237, 0.632726314334, 0.975346415335, 0.792322967224, 0.818420333682, 0.612357534169, 0.808599953565, 0.750349517867, 0.941781682746, 0.886296728549, 0.765147295877, 0.613665348767, 0.50926959983, 0.141692860487, 0.375809101401, 0.505897837434, 0.643984299719, 0.240813673572, 0.187611326103, 0.694456785294, 0.801656988883, 0.779988327305, 0.865188945198, 0.837634541096, 0.848186918295, 0.502892974068, 0.300393867748, 0.297974095698, 0.309272437973, 0.597273649917, 0.680148496239, 0.381500789399, 0.284131359706, 0.6468002367, 0.778052452773, 0.0988440492904, 0.356299306069, 0.0481239238447, 0.764088951419, 0.054441413074, 0.351247004469, 0.00594943028152, 0.612037491016, 0.131257532241, 0.817064069882, 0.89628419797, 0.0646376619169, 0.83098678271, 0.95339889187, 0.275795534836, 0.422112125596, 0.490125695462, 0.420791717071, 0.278390602479, 0.718551888087, 0.190233990778, 0.615294759652, 0.670721836051, 0.584962329587, 0.704182394352, 0.168230194948, 0.371000261477, 0.248142937986, 0.369365387485, 0.974484227313, 0.682154014145, 0.521115993469, 0.282457819694, 0.798591045948, 0.243688109198, 0.582864681853, 0.417536816704, 0.368077658277, 0.828830944101, 0.0214837828817, 0.520875561641, 0.276588568146, 0.569595237254, 0.665313429959, 0.263428233368, 0.235953780226, 0.148747980863, 0.0313727818207, 0.440682616328, 0.4393250905, 0.244714451335, 0.74097157511, 0.420620767629, 0.850439268862, 0.210821048211, 0.62574052154, 0.390930352006, 0.432377028487, 0.598708890322, 0.315261513913, 0.676343076546, 0.804256709486, 0.523292760535, 0.386221805187, 0.55086187451, 0.523611988544, 0.551166814489, 0.568261816189, 0.591439894785, 0.00259641409517, 0.288746811119, 0.74258096466, 0.0646881726817, 0.0266346286656, 0.871116137661, 0.447976616279, 0.182634937333, 0.761823464977, 0.639465276258, 0.109580195366, 0.014282819182, 0.51939745934, 0.759805402357, 0.413646448907, 0.831892776388, 0.292600873127, 0.0628614154507, 0.892006292492, 0.667053037093, 0.329629861785, 0.745624340077, 0.77000452688, 0.991430789057, 0.405940179637, 0.452113552391, 0.774328804451, 0.438839105909, 0.00990615328016, 0.0748044896116, 0.164663402437, 0.518412064527, 0.628681957164, 0.121365285386, 0.134612017388, 0.671251513621, 0.316921326785, 0.533523966579, 0.605712404936, 0.994685692875, 0.968684929393, 0.685358275558, 0.357763978455, 0.547021564141, 0.490891216215, 0.608238675942, 0.714330035496, 0.923253321406, 0.622165815497, 0.181558805163, 0.205341072447, 0.518682690722, 0.401058663467, 0.113183087272, 0.572029596941, 0.158557251214, 0.614028160711, 0.0960443325199, 0.117378367936, 0.926016011903, 0.0197948405259, 0.353731254026, 0.116365576021, 0.133481107834, 0.8674754998, 0.30282474921, 0.0401134681629, 0.222966918681, 0.899867271302, 0.149747225361, 0.497852804372, 0.187908362929, 0.59513525461, 0.0779207401515, 0.387832066904, 0.534512860079, 0.435001973605, 0.0514535174347, 0.431655872369, 0.0695174978587, 0.164406740931, 0.6736140094, 0.792385822878, 0.432362836216, 0.445126493249, 0.160070221943, 0.722767624243, 0.195883543167, 0.212139835891, 0.00615796971941, 0.39357977209, 0.204198710453, 0.278769803212, 0.152537828888, 0.721264031825, 0.075077900285, 0.193542824713, 0.159577346824, 0.0558036459167, 0.623430670079, 0.42922895263, 0.831849522716, 0.672626060889, 0.152016691051, 0.375569068326, 0.530971511933, 0.43972713025, 0.218143410649, 0.337345545141, 0.62346202353, 0.674406857588, 0.907701325394, 0.191578859682, 0.973496576722, 0.191027653366, 0.132196295988, 0.0408926101805, 0.66795021491, 0.485163388421, 0.135249391011, 0.746158252371, 0.0267896825082, 0.577268565219, 0.312933305096, 0.602064894157, 0.163226142437, 0.731927564153, 0.99387665936, 0.390377746604, 0.216360759121, 0.790658032093, 0.872842294152, 0.0607775178149, 0.175294041549, 0.167925818273, 0.7958172331, 0.932698104871, 0.639658432054, 0.635528515864, 0.736740404047, 0.720576693247, 0.652253968617, 0.404912851437, 0.590671586883, 0.559354571615, 0.869038600029, 0.797922625552, 0.750069822131, 0.437528537397, 0.433667482119, 0.470809517135, 0.944689556033, 0.287115206092, 0.490774474696, 0.735826290928, 0.405523654697, 0.518622502098, 0.610593127903, 0.959013454239, 0.384532337582, 0.510027547391, 0.268349089484, 0.888717256149, 0.319687078558, 0.344401565072, 0.0508630403793, 0.702829938164, 0.117301123492, 0.714974774552, 0.426611852737, 0.853801080312, 0.776171443583, 0.933403851327, 0.596645556346, 0.360054218835, 0.0622562830553, 0.67027071599, 0.913447368654, 0.956719780065, 0.511557705678, 0.906949029351, 0.0450473174456, 0.376562021669, 0.285583911368, 0.0950476791492, 0.406053246347, 0.902248242377, 0.410702660062, 0.344914629309, 0.728452570965, 0.0391456991996, 0.936263573762, 0.746529481444, 0.336187297382, 0.741597439999, 0.868316193794, 0.376776624241, 0.460579472794, 0.804512236626, 0.0227148815049, 0.636165887279, 0.771031993532, 0.745494357278, 0.698142520813, 0.426431456408, 0.758342772391, 0.917524665418, 0.310860349564, 0.067982656976, 0.77871909339, 0.813233921395, 0.228562908823, 0.613816102045, 0.294884516699, 0.386414556681, 0.62531278088, 0.681153634462, 0.907553662765, 0.889231846681, 0.214766531376, 0.92489334395, 0.622595062963, 0.454968440986, 0.953223226465, 0.0572546543812, 0.597325190501, 0.452880744022, 0.929418695316, 0.433171547631, 0.659286598303, 0.813287918851, 0.544084024429, 0.362390364156, 0.439847429885, 0.0993499686015, 0.153154068705, 0.094264205672, 0.692948223808, 0.0906710087173, 0.524439077336, 0.568046014133, 0.132580556507, 0.443869752439, 0.186221374828, 0.426861018419, 0.641486281586, 0.160467263993, 0.576186081909, 0.800548711636, 0.368869244596, 0.884472025331, 0.487494254469, 0.657131259037, 0.507997948252, 0.42626813281, 0.966619650333, 0.759827505328, 0.244908168311, 0.38468604666, 0.938963822504, 0.262811760473, 0.01251790648, 0.875503825983, 0.285922863869, 0.895295092449, 0.857246448066, 0.928460148688, 0.69179894932, 0.650775227953, 0.332153657622, 0.753179422259, 0.43378880784, 0.202164319525, 0.608688226551, 0.835945276337, 0.818801474298, 0.470167091131, 0.085874435452, 0.00305111607257, 0.752219158867, 0.928986766867, 0.436791945754, 0.119660045194, 0.264007626898, 0.0347042377661, 0.244955649857, 0.729565745246, 0.744574953959, 0.816386581181, 0.493529907185, 0.976909330758, 0.153331492876, 0.184251923548, 0.761630268628, 0.329417199872, 0.612487481773, 0.776732975207, 0.48685272803, 0.729707657608, 0.691711913231, 0.266936232415, 0.184945883313, 0.541142361971, 0.662811358443, 0.871176671791, 0.170501764892, 0.211110614545, 0.016785787141, 0.763680009265, 0.423290765725, 0.0867251921512, 0.885176947845, 0.900887292602, 0.43366973255, 0.0969804356783, 0.104355881094, 0.692988648892, 0.155816444813, 0.403166342376, 0.73249006134, 0.133241355837, 0.43888269889, 0.384071468204, 0.385372745179, 0.892111652802, 0.225374575618, 0.642079700843, 0.111073179871, 0.38595373134, 0.75516660771, 0.62581076704, 0.205244271564, 0.691904661147, 0.521228580678, 0.258295644083, 0.0725218773237, 0.267323354664, 0.5950189063, 0.385053752659, 0.537727422115, 0.6208819596, 0.101353536341, 0.677557135523, 0.182571209469, 0.454866354541, 0.0245198461588, 0.263099706745, 0.299081687848, 0.0724924397247, 0.111889584823, 0.670772338842, 0.782357595441, 0.0609798619505, 0.10434222192, 0.705278615029, 0.373214050017, 0.36741459391, 0.144112112978, 0.142137350188, 0.282236936635, 0.188277989421, 0.736437218631, 0.717294396392, 0.429028531794, 0.957868912171, 0.698953048058, 0.344024902445, 0.147004384453, 0.236069893678, 0.922829102683, 0.343330732716, 0.930829510577, 0.688362203957, 0.956043878882, 0.901294775516, 0.0619950135736, 0.573480996509, 0.334841074737, 0.894060918004, 0.218546010901, 0.283710469485, 0.335894313583, 0.139991963432, 0.143419311103, 0.805126251245, 0.373897047014, 0.0544683980622, 0.789152824525, 0.0297358977393, 0.442787607394, 0.844954843596, 0.602335852949, 0.606212975355, 0.156857445207, 0.804117877613, 0.442621663161, 0.130769265903, 0.978259945946, 0.533526702041, 0.827885416716, 0.105072902438, 0.106534726834, 0.224529912815, 0.0307191055786, 0.705284299381, 0.80663192533, 0.638722360223, 0.638245219435, 0.340341674858, 0.0695781472208, 0.217392827137, 0.281156286194, 0.693401271469, 0.347762715789};

StableRandom::StableRandom(int seed) : currindex(seed % 1024)
{
}


float StableRandom::Random(float min, float max)
{
   if (max < min) return 0;
   float size = max - min;
   float retval = (size * (vals[currindex]) + min);
   currindex = (currindex + 1) % 1024;
   return retval;
}


void StableRandom::Seed(int seed)
{
   currindex = seed % 1024;
}

