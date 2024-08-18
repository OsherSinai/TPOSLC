/*
	TPOSLC
	A LibC implementation for TPOS (Testing and Prototyping Operating System).

	Copyright © 2024 by Osher Sinai.

	This file is part of TPOSLC (Testing and Prototyping Operating System LibC).

	TPOSLC is free software:
	you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation,
	either version 3 of the License, or (at your option) any later version.

	TPOSLC is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
	without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
	See the GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along with TPOSLC.
	If not, see <https://www.gnu.org/licenses/>.
*/
#pragma once
#ifndef WIN32_TZRES_DLL_H
#define WIN32_TZRES_DLL_H
#ifdef _WIN32
constexpr const char* g_tzres[] = {
	"",//rsc string 0
	"",//rsc string 1
	"",//rsc string 2
	"",//rsc string 3
	"",//rsc string 4
	"",//rsc string 5
	"",//rsc string 6
	"",//rsc string 7
	"",//rsc string 8
	"",//rsc string 9
	"(UTC-01:00) Azores",//rsc string 10
	"Azores Daylight Time",//rsc string 11
	"Azores Standard Time",//rsc string 12
	"",//rsc string 13
	"",//rsc string 14
	"",//rsc string 15
	"",//rsc string 16
	"",//rsc string 17
	"",//rsc string 18
	"",//rsc string 19
	"(UTC-01:00) Cape Verde Is.",//rsc string 20
	"Cape Verde Daylight Time",//rsc string 21
	"Cape Verde Standard Time",//rsc string 22
	"",//rsc string 23
	"",//rsc string 24
	"",//rsc string 25
	"",//rsc string 26
	"",//rsc string 27
	"",//rsc string 28
	"",//rsc string 29
	"(UTC-02:00) Mid-Atlantic",//rsc string 30
	"Mid-Atlantic Daylight Time",//rsc string 31
	"Mid-Atlantic Standard Time",//rsc string 32
	"",//rsc string 33
	"",//rsc string 34
	"",//rsc string 35
	"",//rsc string 36
	"",//rsc string 37
	"",//rsc string 38
	"",//rsc string 39
	"(UTC-03:00) Brasilia",//rsc string 40
	"E. South America Daylight Time",//rsc string 41
	"E. South America Standard Time",//rsc string 42
	"",//rsc string 43
	"",//rsc string 44
	"",//rsc string 45
	"",//rsc string 46
	"",//rsc string 47
	"",//rsc string 48
	"",//rsc string 49
	"(UTC-03:00) Greenland",//rsc string 50
	"Greenland Daylight Time",//rsc string 51
	"Greenland Standard Time",//rsc string 52
	"",//rsc string 53
	"",//rsc string 54
	"",//rsc string 55
	"",//rsc string 56
	"",//rsc string 57
	"",//rsc string 58
	"",//rsc string 59
	"(UTC-03:00) Buenos Aires, Georgetown",//rsc string 60
	"SA Eastern Daylight Time",//rsc string 61
	"SA Eastern Standard Time",//rsc string 62
	"",//rsc string 63
	"",//rsc string 64
	"",//rsc string 65
	"",//rsc string 66
	"",//rsc string 67
	"",//rsc string 68
	"",//rsc string 69
	"(UTC-03:30) Newfoundland",//rsc string 70
	"Newfoundland Daylight Time",//rsc string 71
	"Newfoundland Standard Time",//rsc string 72
	"",//rsc string 73
	"",//rsc string 74
	"",//rsc string 75
	"",//rsc string 76
	"",//rsc string 77
	"",//rsc string 78
	"",//rsc string 79
	"(UTC-04:00) Atlantic Time (Canada)",//rsc string 80
	"Atlantic Daylight Time",//rsc string 81
	"Atlantic Standard Time",//rsc string 82
	"",//rsc string 83
	"",//rsc string 84
	"",//rsc string 85
	"",//rsc string 86
	"",//rsc string 87
	"",//rsc string 88
	"",//rsc string 89
	"(UTC-04:00) Santiago",//rsc string 90
	"Pacific SA Daylight Time",//rsc string 91
	"Pacific SA Standard Time",//rsc string 92
	"",//rsc string 93
	"",//rsc string 94
	"",//rsc string 95
	"",//rsc string 96
	"",//rsc string 97
	"",//rsc string 98
	"",//rsc string 99
	"(UTC-04:00) Caracas, La Paz",//rsc string 100
	"SA Western Daylight Time",//rsc string 101
	"SA Western Standard Time",//rsc string 102
	"(UTC-04:00) Manaus",//rsc string 103
	"Central Brazilian Daylight Time",//rsc string 104
	"Central Brazilian Standard Time",//rsc string 105
	"",//rsc string 106
	"",//rsc string 107
	"",//rsc string 108
	"",//rsc string 109
	"(UTC-05:00) Eastern Time (US & Canada)",//rsc string 110
	"Eastern Daylight Time",//rsc string 111
	"Eastern Standard Time",//rsc string 112
	"",//rsc string 113
	"",//rsc string 114
	"",//rsc string 115
	"",//rsc string 116
	"",//rsc string 117
	"",//rsc string 118
	"",//rsc string 119
	"(UTC-05:00) Bogota, Lima, Quito, Rio Branco",//rsc string 120
	"SA Pacific Daylight Time",//rsc string 121
	"SA Pacific Standard Time",//rsc string 122
	"",//rsc string 123
	"",//rsc string 124
	"",//rsc string 125
	"",//rsc string 126
	"",//rsc string 127
	"",//rsc string 128
	"",//rsc string 129
	"(UTC-05:00) Indiana (East)",//rsc string 130
	"US Eastern Daylight Time",//rsc string 131
	"US Eastern Standard Time",//rsc string 132
	"",//rsc string 133
	"",//rsc string 134
	"",//rsc string 135
	"",//rsc string 136
	"",//rsc string 137
	"",//rsc string 138
	"",//rsc string 139
	"(UTC-06:00) Saskatchewan",//rsc string 140
	"Canada Central Daylight Time",//rsc string 141
	"Canada Central Standard Time",//rsc string 142
	"",//rsc string 143
	"",//rsc string 144
	"",//rsc string 145
	"",//rsc string 146
	"",//rsc string 147
	"",//rsc string 148
	"",//rsc string 149
	"(UTC-06:00) Central America",//rsc string 150
	"Central America Daylight Time",//rsc string 151
	"Central America Standard Time",//rsc string 152
	"",//rsc string 153
	"",//rsc string 154
	"",//rsc string 155
	"",//rsc string 156
	"",//rsc string 157
	"",//rsc string 158
	"",//rsc string 159
	"(UTC-06:00) Central Time (US & Canada)",//rsc string 160
	"Central Daylight Time",//rsc string 161
	"Central Standard Time",//rsc string 162
	"",//rsc string 163
	"",//rsc string 164
	"",//rsc string 165
	"",//rsc string 166
	"",//rsc string 167
	"",//rsc string 168
	"",//rsc string 169
	"(UTC-06:00) Guadalajara, Mexico City, Monterrey",//rsc string 170
	"Central Daylight Time (Mexico)",//rsc string 171
	"Central Standard Time (Mexico)",//rsc string 172
	"",//rsc string 173
	"",//rsc string 174
	"",//rsc string 175
	"",//rsc string 176
	"",//rsc string 177
	"",//rsc string 178
	"",//rsc string 179
	"(UTC-07:00) Chihuahua, La Paz, Mazatlan",//rsc string 180
	"Mountain Daylight Time (Mexico)",//rsc string 181
	"Mountain Standard Time (Mexico)",//rsc string 182
	"",//rsc string 183
	"",//rsc string 184
	"",//rsc string 185
	"",//rsc string 186
	"",//rsc string 187
	"",//rsc string 188
	"",//rsc string 189
	"(UTC-07:00) Mountain Time (US & Canada)",//rsc string 190
	"Mountain Daylight Time",//rsc string 191
	"Mountain Standard Time",//rsc string 192
	"",//rsc string 193
	"",//rsc string 194
	"",//rsc string 195
	"",//rsc string 196
	"",//rsc string 197
	"",//rsc string 198
	"",//rsc string 199
	"(UTC-07:00) Arizona",//rsc string 200
	"US Mountain Daylight Time",//rsc string 201
	"US Mountain Standard Time",//rsc string 202
	"",//rsc string 203
	"",//rsc string 204
	"",//rsc string 205
	"",//rsc string 206
	"",//rsc string 207
	"",//rsc string 208
	"",//rsc string 209
	"(UTC-08:00) Pacific Time (US & Canada)",//rsc string 210
	"Pacific Daylight Time",//rsc string 211
	"Pacific Standard Time",//rsc string 212
	"(UTC-08:00) Tijuana, Baja California",//rsc string 213
	"Pacific Daylight Time (Mexico)",//rsc string 214
	"Pacific Standard Time (Mexico)",//rsc string 215
	"",//rsc string 216
	"",//rsc string 217
	"",//rsc string 218
	"",//rsc string 219
	"(UTC-09:00) Alaska",//rsc string 220
	"Alaskan Daylight Time",//rsc string 221
	"Alaskan Standard Time",//rsc string 222
	"",//rsc string 223
	"",//rsc string 224
	"",//rsc string 225
	"",//rsc string 226
	"",//rsc string 227
	"",//rsc string 228
	"",//rsc string 229
	"(UTC-10:00) Hawaii",//rsc string 230
	"Hawaiian Daylight Time",//rsc string 231
	"Hawaiian Standard Time",//rsc string 232
	"",//rsc string 233
	"",//rsc string 234
	"",//rsc string 235
	"",//rsc string 236
	"",//rsc string 237
	"",//rsc string 238
	"",//rsc string 239
	"(UTC-11:00) Midway Island, Samoa",//rsc string 240
	"Samoa Daylight Time",//rsc string 241
	"Samoa Standard Time",//rsc string 242
	"",//rsc string 243
	"",//rsc string 244
	"",//rsc string 245
	"",//rsc string 246
	"",//rsc string 247
	"",//rsc string 248
	"",//rsc string 249
	"(UTC-12:00) International Date Line West",//rsc string 250
	"Dateline Daylight Time",//rsc string 251
	"Dateline Standard Time",//rsc string 252
	"",//rsc string 253
	"",//rsc string 254
	"",//rsc string 255
	"",//rsc string 256
	"",//rsc string 257
	"",//rsc string 258
	"",//rsc string 259
	"(UTC) Dublin, Edinburgh, Lisbon, London",//rsc string 260
	"GMT Daylight Time",//rsc string 261
	"GMT Standard Time",//rsc string 262
	"",//rsc string 263
	"",//rsc string 264
	"",//rsc string 265
	"",//rsc string 266
	"",//rsc string 267
	"",//rsc string 268
	"",//rsc string 269
	"(UTC) Casablanca, Monrovia, Reykjavik",//rsc string 270
	"Greenwich Daylight Time",//rsc string 271
	"Greenwich Standard Time",//rsc string 272
	"",//rsc string 273
	"",//rsc string 274
	"",//rsc string 275
	"",//rsc string 276
	"",//rsc string 277
	"",//rsc string 278
	"",//rsc string 279
	"(UTC+01:00) Belgrade, Bratislava, Budapest, Ljubljana, Prague",//rsc string 280
	"Central Europe Daylight Time",//rsc string 281
	"Central Europe Standard Time",//rsc string 282
	"",//rsc string 283
	"",//rsc string 284
	"",//rsc string 285
	"",//rsc string 286
	"",//rsc string 287
	"",//rsc string 288
	"",//rsc string 289
	"(UTC+01:00) Sarajevo, Skopje, Warsaw, Zagreb",//rsc string 290
	"Central European Daylight Time",//rsc string 291
	"Central European Standard Time",//rsc string 292
	"",//rsc string 293
	"",//rsc string 294
	"",//rsc string 295
	"",//rsc string 296
	"",//rsc string 297
	"",//rsc string 298
	"",//rsc string 299
	"(UTC+01:00) Brussels, Copenhagen, Madrid, Paris",//rsc string 300
	"Romance Daylight Time",//rsc string 301
	"Romance Standard Time",//rsc string 302
	"",//rsc string 303
	"",//rsc string 304
	"",//rsc string 305
	"",//rsc string 306
	"",//rsc string 307
	"",//rsc string 308
	"",//rsc string 309
	"(UTC+01:00) West Central Africa",//rsc string 310
	"W. Central Africa Daylight Time",//rsc string 311
	"W. Central Africa Standard Time",//rsc string 312
	"",//rsc string 313
	"",//rsc string 314
	"",//rsc string 315
	"",//rsc string 316
	"",//rsc string 317
	"",//rsc string 318
	"",//rsc string 319
	"(UTC+01:00) Amsterdam, Berlin, Bern, Rome, Stockholm, Vienna",//rsc string 320
	"W. Europe Daylight Time",//rsc string 321
	"W. Europe Standard Time",//rsc string 322
	"",//rsc string 323
	"",//rsc string 324
	"",//rsc string 325
	"",//rsc string 326
	"",//rsc string 327
	"",//rsc string 328
	"",//rsc string 329
	"(UTC+02:00) Minsk",//rsc string 330
	"E. Europe Daylight Time",//rsc string 331
	"E. Europe Standard Time",//rsc string 332
	"(UTC+02:00) Amman",//rsc string 333
	"Jordan Daylight Time",//rsc string 334
	"Jordan Standard Time",//rsc string 335
	"",//rsc string 336
	"",//rsc string 337
	"",//rsc string 338
	"",//rsc string 339
	"(UTC+02:00) Cairo",//rsc string 340
	"Egypt Daylight Time",//rsc string 341
	"Egypt Standard Time",//rsc string 342
	"",//rsc string 343
	"",//rsc string 344
	"",//rsc string 345
	"",//rsc string 346
	"",//rsc string 347
	"",//rsc string 348
	"",//rsc string 349
	"(UTC+02:00) Helsinki, Kyiv, Riga, Sofia, Tallinn, Vilnius",//rsc string 350
	"FLE Daylight Time",//rsc string 351
	"FLE Standard Time",//rsc string 352
	"",//rsc string 353
	"",//rsc string 354
	"",//rsc string 355
	"",//rsc string 356
	"",//rsc string 357
	"",//rsc string 358
	"",//rsc string 359
	"(UTC+02:00) Athens, Bucharest, Istanbul",//rsc string 360
	"GTB Daylight Time",//rsc string 361
	"GTB Standard Time",//rsc string 362
	"(UTC+02:00) Beirut",//rsc string 363
	"Middle East Daylight Time",//rsc string 364
	"Middle East Standard Time",//rsc string 365
	"",//rsc string 366
	"",//rsc string 367
	"",//rsc string 368
	"",//rsc string 369
	"(UTC+02:00) Jerusalem",//rsc string 370
	"Jerusalem Daylight Time",//rsc string 371
	"Jerusalem Standard Time",//rsc string 372
	"",//rsc string 373
	"",//rsc string 374
	"",//rsc string 375
	"",//rsc string 376
	"",//rsc string 377
	"",//rsc string 378
	"",//rsc string 379
	"(UTC+02:00) Harare, Pretoria",//rsc string 380
	"South Africa Daylight Time",//rsc string 381
	"South Africa Standard Time",//rsc string 382
	"(UTC+02:00) Windhoek",//rsc string 383
	"Namibia Daylight Time",//rsc string 384
	"Namibia Standard Time",//rsc string 385
	"",//rsc string 386
	"",//rsc string 387
	"",//rsc string 388
	"",//rsc string 389
	"(UTC+03:00) Kuwait, Riyadh",//rsc string 390
	"Arab Daylight Time",//rsc string 391
	"Arab Standard Time",//rsc string 392
	"",//rsc string 393
	"",//rsc string 394
	"",//rsc string 395
	"",//rsc string 396
	"",//rsc string 397
	"",//rsc string 398
	"",//rsc string 399
	"(UTC+03:00) Baghdad",//rsc string 400
	"Arabic Daylight Time",//rsc string 401
	"Arabic Standard Time",//rsc string 402
	"",//rsc string 403
	"",//rsc string 404
	"",//rsc string 405
	"",//rsc string 406
	"",//rsc string 407
	"",//rsc string 408
	"",//rsc string 409
	"(UTC+03:00) Nairobi",//rsc string 410
	"E. Africa Daylight Time",//rsc string 411
	"E. Africa Standard Time",//rsc string 412
	"",//rsc string 413
	"",//rsc string 414
	"",//rsc string 415
	"",//rsc string 416
	"",//rsc string 417
	"",//rsc string 418
	"",//rsc string 419
	"(UTC+03:00) Moscow, St. Petersburg, Volgograd",//rsc string 420
	"Russian Daylight Time",//rsc string 421
	"Russian Standard Time",//rsc string 422
	"",//rsc string 423
	"",//rsc string 424
	"",//rsc string 425
	"",//rsc string 426
	"",//rsc string 427
	"",//rsc string 428
	"",//rsc string 429
	"(UTC+03:30) Tehran",//rsc string 430
	"Iran Daylight Time",//rsc string 431
	"Iran Standard Time",//rsc string 432
	"(UTC+03:00) Tbilisi",//rsc string 433
	"Georgian Daylight Time",//rsc string 434
	"Georgian Standard Time",//rsc string 435
	"",//rsc string 436
	"",//rsc string 437
	"",//rsc string 438
	"",//rsc string 439
	"(UTC+04:00) Abu Dhabi, Muscat",//rsc string 440
	"Arabian Daylight Time",//rsc string 441
	"Arabian Standard Time",//rsc string 442
	"",//rsc string 443
	"",//rsc string 444
	"",//rsc string 445
	"",//rsc string 446
	"(UTC+04:00) Baku",//rsc string 447
	"Azerbaijan Daylight Time",//rsc string 448
	"Azerbaijan Standard Time",//rsc string 449
	"(UTC+04:00) Yerevan",//rsc string 450
	"Caucasus Daylight Time",//rsc string 451
	"Caucasus Standard Time",//rsc string 452
	"",//rsc string 453
	"",//rsc string 454
	"",//rsc string 455
	"",//rsc string 456
	"",//rsc string 457
	"",//rsc string 458
	"",//rsc string 459
	"(UTC+04:30) Kabul",//rsc string 460
	"Afghanistan Daylight Time",//rsc string 461
	"Afghanistan Standard Time",//rsc string 462
	"",//rsc string 463
	"",//rsc string 464
	"",//rsc string 465
	"",//rsc string 466
	"",//rsc string 467
	"",//rsc string 468
	"",//rsc string 469
	"(UTC+05:00) Ekaterinburg",//rsc string 470
	"Ekaterinburg Daylight Time",//rsc string 471
	"Ekaterinburg Standard Time",//rsc string 472
	"",//rsc string 473
	"",//rsc string 474
	"",//rsc string 475
	"",//rsc string 476
	"",//rsc string 477
	"",//rsc string 478
	"",//rsc string 479
	"(UTC+05:00) Islamabad, Karachi, Tashkent",//rsc string 480
	"West Asia Daylight Time",//rsc string 481
	"West Asia Standard Time",//rsc string 482
	"",//rsc string 483
	"",//rsc string 484
	"",//rsc string 485
	"",//rsc string 486
	"",//rsc string 487
	"",//rsc string 488
	"",//rsc string 489
	"(UTC+05:30) Chennai, Kolkata, Mumbai, New Delhi",//rsc string 490
	"India Daylight Time",//rsc string 491
	"India Standard Time",//rsc string 492
	"",//rsc string 493
	"",//rsc string 494
	"",//rsc string 495
	"",//rsc string 496
	"",//rsc string 497
	"",//rsc string 498
	"",//rsc string 499
	"(UTC+05:45) Kathmandu",//rsc string 500
	"Nepal Daylight Time",//rsc string 501
	"Nepal Standard Time",//rsc string 502
	"",//rsc string 503
	"",//rsc string 504
	"",//rsc string 505
	"",//rsc string 506
	"",//rsc string 507
	"",//rsc string 508
	"",//rsc string 509
	"(UTC+06:00) Astana, Dhaka",//rsc string 510
	"Central Asia Daylight Time",//rsc string 511
	"Central Asia Standard Time",//rsc string 512
	"",//rsc string 513
	"",//rsc string 514
	"",//rsc string 515
	"",//rsc string 516
	"",//rsc string 517
	"",//rsc string 518
	"",//rsc string 519
	"(UTC+06:00) Almaty, Novosibirsk",//rsc string 520
	"N. Central Asia Daylight Time",//rsc string 521
	"N. Central Asia Standard Time",//rsc string 522
	"",//rsc string 523
	"",//rsc string 524
	"",//rsc string 525
	"",//rsc string 526
	"",//rsc string 527
	"",//rsc string 528
	"",//rsc string 529
	"(UTC+05:30) Sri Jayawardenepura",//rsc string 530
	"Sri Lanka Daylight Time",//rsc string 531
	"Sri Lanka Standard Time",//rsc string 532
	"",//rsc string 533
	"",//rsc string 534
	"",//rsc string 535
	"",//rsc string 536
	"",//rsc string 537
	"",//rsc string 538
	"",//rsc string 539
	"(UTC+06:30) Yangon (Rangoon)",//rsc string 540
	"Myanmar Daylight Time",//rsc string 541
	"Myanmar Standard Time",//rsc string 542
	"",//rsc string 543
	"",//rsc string 544
	"",//rsc string 545
	"",//rsc string 546
	"",//rsc string 547
	"",//rsc string 548
	"",//rsc string 549
	"(UTC+07:00) Krasnoyarsk",//rsc string 550
	"North Asia Daylight Time",//rsc string 551
	"North Asia Standard Time",//rsc string 552
	"",//rsc string 553
	"",//rsc string 554
	"",//rsc string 555
	"",//rsc string 556
	"",//rsc string 557
	"",//rsc string 558
	"",//rsc string 559
	"(UTC+07:00) Bangkok, Hanoi, Jakarta",//rsc string 560
	"SE Asia Daylight Time",//rsc string 561
	"SE Asia Standard Time",//rsc string 562
	"",//rsc string 563
	"",//rsc string 564
	"",//rsc string 565
	"",//rsc string 566
	"",//rsc string 567
	"",//rsc string 568
	"",//rsc string 569
	"(UTC+08:00) Beijing, Chongqing, Hong Kong, Urumqi",//rsc string 570
	"China Daylight Time",//rsc string 571
	"China Standard Time",//rsc string 572
	"",//rsc string 573
	"",//rsc string 574
	"",//rsc string 575
	"",//rsc string 576
	"",//rsc string 577
	"",//rsc string 578
	"",//rsc string 579
	"(UTC+08:00) Irkutsk, Ulaan Bataar",//rsc string 580
	"North Asia East Daylight Time",//rsc string 581
	"North Asia East Standard Time",//rsc string 582
	"",//rsc string 583
	"",//rsc string 584
	"",//rsc string 585
	"",//rsc string 586
	"",//rsc string 587
	"",//rsc string 588
	"",//rsc string 589
	"(UTC+08:00) Kuala Lumpur, Singapore",//rsc string 590
	"Malay Peninsula Daylight Time",//rsc string 591
	"Malay Peninsula Standard Time",//rsc string 592
	"",//rsc string 593
	"",//rsc string 594
	"",//rsc string 595
	"",//rsc string 596
	"",//rsc string 597
	"",//rsc string 598
	"",//rsc string 599
	"(UTC+08:00) Taipei",//rsc string 600
	"Taipei Daylight Time",//rsc string 601
	"Taipei Standard Time",//rsc string 602
	"",//rsc string 603
	"",//rsc string 604
	"",//rsc string 605
	"",//rsc string 606
	"",//rsc string 607
	"",//rsc string 608
	"",//rsc string 609
	"(UTC+08:00) Perth",//rsc string 610
	"W. Australia Daylight Time",//rsc string 611
	"W. Australia Standard Time",//rsc string 612
	"",//rsc string 613
	"",//rsc string 614
	"",//rsc string 615
	"",//rsc string 616
	"",//rsc string 617
	"",//rsc string 618
	"",//rsc string 619
	"(UTC+09:00) Seoul",//rsc string 620
	"Korea Daylight Time",//rsc string 621
	"Korea Standard Time",//rsc string 622
	"",//rsc string 623
	"",//rsc string 624
	"",//rsc string 625
	"",//rsc string 626
	"",//rsc string 627
	"",//rsc string 628
	"",//rsc string 629
	"(UTC+09:00) Osaka, Sapporo, Tokyo",//rsc string 630
	"Tokyo Daylight Time",//rsc string 631
	"Tokyo Standard Time",//rsc string 632
	"",//rsc string 633
	"",//rsc string 634
	"",//rsc string 635
	"",//rsc string 636
	"",//rsc string 637
	"",//rsc string 638
	"",//rsc string 639
	"(UTC+09:00) Yakutsk",//rsc string 640
	"Yakutsk Daylight Time",//rsc string 641
	"Yakutsk Standard Time",//rsc string 642
	"",//rsc string 643
	"",//rsc string 644
	"",//rsc string 645
	"",//rsc string 646
	"",//rsc string 647
	"",//rsc string 648
	"",//rsc string 649
	"(UTC+09:30) Darwin",//rsc string 650
	"AUS Central Daylight Time",//rsc string 651
	"AUS Central Standard Time",//rsc string 652
	"",//rsc string 653
	"",//rsc string 654
	"",//rsc string 655
	"",//rsc string 656
	"",//rsc string 657
	"",//rsc string 658
	"",//rsc string 659
	"(UTC+09:30) Adelaide",//rsc string 660
	"Cen. Australia Daylight Time",//rsc string 661
	"Cen. Australia Standard Time",//rsc string 662
	"",//rsc string 663
	"",//rsc string 664
	"",//rsc string 665
	"",//rsc string 666
	"",//rsc string 667
	"",//rsc string 668
	"",//rsc string 669
	"(UTC+10:00) Canberra, Melbourne, Sydney",//rsc string 670
	"AUS Eastern Daylight Time",//rsc string 671
	"AUS Eastern Standard Time",//rsc string 672
	"",//rsc string 673
	"",//rsc string 674
	"",//rsc string 675
	"",//rsc string 676
	"",//rsc string 677
	"",//rsc string 678
	"",//rsc string 679
	"(UTC+10:00) Brisbane",//rsc string 680
	"E. Australia Daylight Time",//rsc string 681
	"E. Australia Standard Time",//rsc string 682
	"",//rsc string 683
	"",//rsc string 684
	"",//rsc string 685
	"",//rsc string 686
	"",//rsc string 687
	"",//rsc string 688
	"",//rsc string 689
	"(UTC+10:00) Hobart",//rsc string 690
	"Tasmania Daylight Time",//rsc string 691
	"Tasmania Standard Time",//rsc string 692
	"",//rsc string 693
	"",//rsc string 694
	"",//rsc string 695
	"",//rsc string 696
	"",//rsc string 697
	"",//rsc string 698
	"",//rsc string 699
	"(UTC+10:00) Vladivostok",//rsc string 700
	"Vladivostok Daylight Time",//rsc string 701
	"Vladivostok Standard Time",//rsc string 702
	"",//rsc string 703
	"",//rsc string 704
	"",//rsc string 705
	"",//rsc string 706
	"",//rsc string 707
	"",//rsc string 708
	"",//rsc string 709
	"(UTC+10:00) Guam, Port Moresby",//rsc string 710
	"West Pacific Daylight Time",//rsc string 711
	"West Pacific Standard Time",//rsc string 712
	"",//rsc string 713
	"",//rsc string 714
	"",//rsc string 715
	"",//rsc string 716
	"",//rsc string 717
	"",//rsc string 718
	"",//rsc string 719
	"(UTC+11:00) Magadan, Solomon Is., New Caledonia",//rsc string 720
	"Central Pacific Daylight Time",//rsc string 721
	"Central Pacific Standard Time",//rsc string 722
	"",//rsc string 723
	"",//rsc string 724
	"",//rsc string 725
	"",//rsc string 726
	"",//rsc string 727
	"",//rsc string 728
	"",//rsc string 729
	"(UTC+12:00) Fiji, Kamchatka, Marshall Is.",//rsc string 730
	"Fiji Daylight Time",//rsc string 731
	"Fiji Standard Time",//rsc string 732
	"",//rsc string 733
	"",//rsc string 734
	"",//rsc string 735
	"",//rsc string 736
	"",//rsc string 737
	"",//rsc string 738
	"",//rsc string 739
	"(UTC+12:00) Auckland, Wellington",//rsc string 740
	"New Zealand Daylight Time",//rsc string 741
	"New Zealand Standard Time",//rsc string 742
	"",//rsc string 743
	"",//rsc string 744
	"",//rsc string 745
	"",//rsc string 746
	"",//rsc string 747
	"",//rsc string 748
	"",//rsc string 749
	"(UTC+13:00) Nuku'alofa",//rsc string 750
	"Tonga Daylight Time",//rsc string 751
	"Tonga Standard Time",//rsc string 752
	"",//rsc string 753
	"",//rsc string 754
	"",//rsc string 755
	"",//rsc string 756
	"",//rsc string 757
	"",//rsc string 758
	"",//rsc string 759
	"",//rsc string 760
	"",//rsc string 761
	"",//rsc string 762
	"",//rsc string 763
	"",//rsc string 764
	"",//rsc string 765
	"",//rsc string 766
	"",//rsc string 767
	"",//rsc string 768
	"",//rsc string 769
	"(UTC-03:00) Montevideo",//rsc string 770
	"Montevideo Daylight Time",//rsc string 771
	"Montevideo Standard Time",//rsc string 772
	"",//rsc string 773
	"",//rsc string 774
	"",//rsc string 775
	"",//rsc string 776
	"",//rsc string 777
	"",//rsc string 778
	"",//rsc string 779
	"",//rsc string 780
	"",//rsc string 781
	"",//rsc string 782
	"",//rsc string 783
	"",//rsc string 784
	"",//rsc string 785
	"",//rsc string 786
	"",//rsc string 787
	"",//rsc string 788
	"",//rsc string 789
	"(UTC-04:00) La Paz",//rsc string 790
	"SA Western Daylight Time",//rsc string 791
	"SA Western Standard Time",//rsc string 792
	"",//rsc string 793
	"",//rsc string 794
	"",//rsc string 795
	"",//rsc string 796
	"",//rsc string 797
	"",//rsc string 798
	"",//rsc string 799
	"",//rsc string 800
	"",//rsc string 801
	"",//rsc string 802
	"",//rsc string 803
	"",//rsc string 804
	"",//rsc string 805
	"",//rsc string 806
	"",//rsc string 807
	"",//rsc string 808
	"",//rsc string 809
	"(UTC-04:30) Caracas",//rsc string 810
	"Venezuela Daylight Time",//rsc string 811
	"Venezuela Standard Time",//rsc string 812
	"",//rsc string 813
	"",//rsc string 814
	"",//rsc string 815
	"",//rsc string 816
	"",//rsc string 817
	"",//rsc string 818
	"",//rsc string 819
	"",//rsc string 820
	"",//rsc string 821
	"",//rsc string 822
	"",//rsc string 823
	"",//rsc string 824
	"",//rsc string 825
	"",//rsc string 826
	"",//rsc string 827
	"",//rsc string 828
	"",//rsc string 829
	"(UTC-03:00) Georgetown",//rsc string 830
	"SA Eastern Daylight Time",//rsc string 831
	"SA Eastern Standard Time",//rsc string 832
	"",//rsc string 833
	"",//rsc string 834
	"",//rsc string 835
	"",//rsc string 836
	"",//rsc string 837
	"",//rsc string 838
	"",//rsc string 839
	"(UTC-03:00) Buenos Aires",//rsc string 840
	"Argentina Daylight Time",//rsc string 841
	"Argentina Standard Time",//rsc string 842
	"",//rsc string 843
	"",//rsc string 844
	"",//rsc string 845
	"",//rsc string 846
	"",//rsc string 847
	"",//rsc string 848
	"",//rsc string 849
	"",//rsc string 850
	"",//rsc string 851
	"",//rsc string 852
	"",//rsc string 853
	"",//rsc string 854
	"",//rsc string 855
	"",//rsc string 856
	"",//rsc string 857
	"",//rsc string 858
	"",//rsc string 859
	"(UTC+05:00) Tashkent",//rsc string 860
	"",//rsc string 861
	"",//rsc string 862
	"",//rsc string 863
	"",//rsc string 864
	"",//rsc string 865
	"",//rsc string 866
	"",//rsc string 867
	"",//rsc string 868
	"",//rsc string 869
	"(UTC+05:00) Islamabad, Karachi",//rsc string 870
	"Pakistan Daylight Time",//rsc string 871
	"Pakistan Standard Time",//rsc string 872
	"",//rsc string 873
	"",//rsc string 874
	"",//rsc string 875
	"",//rsc string 876
	"",//rsc string 877
	"",//rsc string 878
	"",//rsc string 879
	"(UTC) Monrovia, Reykjavik",//rsc string 880
	"",//rsc string 881
	"",//rsc string 882
	"",//rsc string 883
	"",//rsc string 884
	"",//rsc string 885
	"",//rsc string 886
	"",//rsc string 887
	"",//rsc string 888
	"",//rsc string 889
	"(UTC) Casablanca",//rsc string 890
	"Morocco Daylight Time",//rsc string 891
	"Morocco Standard Time",//rsc string 892
	"",//rsc string 893
	"",//rsc string 894
	"",//rsc string 895
	"",//rsc string 896
	"",//rsc string 897
	"",//rsc string 898
	"",//rsc string 899
	"",//rsc string 900
	"",//rsc string 901
	"",//rsc string 902
	"",//rsc string 903
	"",//rsc string 904
	"",//rsc string 905
	"",//rsc string 906
	"",//rsc string 907
	"",//rsc string 908
	"",//rsc string 909
	"(UTC+04:00) Port Louis",//rsc string 910
	"Mauritius Daylight Time",//rsc string 911
	"Mauritius Standard Time",//rsc string 912
	"",//rsc string 913
	"",//rsc string 914
	"",//rsc string 915
	"",//rsc string 916
	"",//rsc string 917
	"",//rsc string 918
	"",//rsc string 919
	"",//rsc string 920
	"",//rsc string 921
	"",//rsc string 922
	"",//rsc string 923
	"",//rsc string 924
	"",//rsc string 925
	"",//rsc string 926
	"",//rsc string 927
	"",//rsc string 928
	"",//rsc string 929
	"(UTC) Coordinated Universal Time",//rsc string 930
	"Coordinated Universal Time",//rsc string 931
	"Coordinated Universal Time",//rsc string 932
	"",//rsc string 933
	"",//rsc string 934
	"",//rsc string 935
	"",//rsc string 936
	"",//rsc string 937
	"",//rsc string 938
	"",//rsc string 939
	"(UTC-03:00) Cayenne",//rsc string 940
	"",//rsc string 941
	"",//rsc string 942
	"",//rsc string 943
	"",//rsc string 944
	"",//rsc string 945
	"",//rsc string 946
	"",//rsc string 947
	"",//rsc string 948
	"",//rsc string 949
	"(UTC-04:00) Georgetown, La Paz, San Juan",//rsc string 950
	"",//rsc string 951
	"",//rsc string 952
	"",//rsc string 953
	"",//rsc string 954
	"",//rsc string 955
	"",//rsc string 956
	"",//rsc string 957
	"",//rsc string 958
	"",//rsc string 959
	"(UTC-04:00) Asuncion",//rsc string 960
	"Paraguay Daylight Time",//rsc string 961
	"Paraguay Standard Time",//rsc string 962
	"",//rsc string 963
	"",//rsc string 964
	"",//rsc string 965
	"",//rsc string 966
	"",//rsc string 967
	"",//rsc string 968
	"",//rsc string 969
	"(UTC+12:00) Fiji, Marshall Is.",//rsc string 970
	"",//rsc string 971
	"",//rsc string 972
	"",//rsc string 973
	"",//rsc string 974
	"",//rsc string 975
	"",//rsc string 976
	"",//rsc string 977
	"",//rsc string 978
	"",//rsc string 979
	"(UTC+12:00) Petropavlovsk-Kamchatsky",//rsc string 980
	"Kamchatka Daylight Time",//rsc string 981
	"Kamchatka Standard Time",//rsc string 982
	"",//rsc string 983
	"",//rsc string 984
	"",//rsc string 985
	"",//rsc string 986
	"",//rsc string 987
	"",//rsc string 988
	"",//rsc string 989
	"(UTC-05:00) Bogota, Lima, Quito",//rsc string 990
	"",//rsc string 991
	"",//rsc string 992
	"",//rsc string 993
	"",//rsc string 994
	"",//rsc string 995
	"",//rsc string 996
	"",//rsc string 997
	"",//rsc string 998
	"",//rsc string 999
	"",//rsc string 1000
	"",//rsc string 1001
	"",//rsc string 1002
	"",//rsc string 1003
	"",//rsc string 1004
	"",//rsc string 1005
	"",//rsc string 1006
	"",//rsc string 1007
	"",//rsc string 1008
	"",//rsc string 1009
	"(UTC+06:00) Astana",//rsc string 1010
	"",//rsc string 1011
	"",//rsc string 1012
	"",//rsc string 1013
	"",//rsc string 1014
	"",//rsc string 1015
	"",//rsc string 1016
	"",//rsc string 1017
	"",//rsc string 1018
	"",//rsc string 1019
	"(UTC+06:00) Dhaka",//rsc string 1020
	"Bangladesh Daylight Time",//rsc string 1021
	"Bangladesh Standard Time",//rsc string 1022
	"",//rsc string 1023
	"",//rsc string 1024
	"",//rsc string 1025
	"",//rsc string 1026
	"",//rsc string 1027
	"",//rsc string 1028
	"",//rsc string 1029
	"(UTC+08:00) Irkutsk",//rsc string 1030
	"",//rsc string 1031
	"",//rsc string 1032
	"",//rsc string 1033
	"",//rsc string 1034
	"",//rsc string 1035
	"",//rsc string 1036
	"",//rsc string 1037
	"",//rsc string 1038
	"",//rsc string 1039
	"(UTC+08:00) Ulaanbaatar",//rsc string 1040
	"Ulaanbaatar Daylight Time",//rsc string 1041
	"Ulaanbaatar Standard Time",//rsc string 1042
	"",//rsc string 1043
	"",//rsc string 1044
	"",//rsc string 1045
	"",//rsc string 1046
	"",//rsc string 1047
	"",//rsc string 1048
	"",//rsc string 1049
	"(UTC-11:00) Samoa",//rsc string 1050
	"",//rsc string 1051
	"",//rsc string 1052
	"",//rsc string 1053
	"",//rsc string 1054
	"",//rsc string 1055
	"",//rsc string 1056
	"",//rsc string 1057
	"",//rsc string 1058
	"",//rsc string 1059
	"(UTC-11:00) Midway Islands",//rsc string 1060
	"North Pacific Daylight Time",//rsc string 1061
	"North Pacific Standard Time",//rsc string 1062
	"",//rsc string 1063
	"",//rsc string 1064
	"",//rsc string 1065
	"",//rsc string 1066
	"",//rsc string 1067
	"",//rsc string 1068
	"",//rsc string 1069
	"(UTC+04:00) Tbilisi",//rsc string 1070
	"",//rsc string 1071
	"",//rsc string 1072
	"",//rsc string 1073
	"",//rsc string 1074
	"",//rsc string 1075
	"",//rsc string 1076
	"",//rsc string 1077
	"",//rsc string 1078
	"",//rsc string 1079
	"(UTC+06:00) Novosibirsk",//rsc string 1080
	"",//rsc string 1081
	"",//rsc string 1082
	"",//rsc string 1083
	"",//rsc string 1084
	"",//rsc string 1085
	"",//rsc string 1086
	"",//rsc string 1087
	"",//rsc string 1088
	"",//rsc string 1089
	"",//rsc string 1090
	"",//rsc string 1091
	"",//rsc string 1092
	"",//rsc string 1093
	"",//rsc string 1094
	"",//rsc string 1095
	"",//rsc string 1096
	"",//rsc string 1097
	"",//rsc string 1098
	"",//rsc string 1099
	"(UTC-08:00) Baja California",//rsc string 1100
	"",//rsc string 1101
	"",//rsc string 1102
	"",//rsc string 1103
	"",//rsc string 1104
	"",//rsc string 1105
	"",//rsc string 1106
	"",//rsc string 1107
	"",//rsc string 1108
	"",//rsc string 1109
	"(UTC-03:00) Cayenne, Fortaleza",//rsc string 1110
	"",//rsc string 1111
	"",//rsc string 1112
	"",//rsc string 1113
	"",//rsc string 1114
	"",//rsc string 1115
	"",//rsc string 1116
	"",//rsc string 1117
	"",//rsc string 1118
	"",//rsc string 1119
	"(UTC-04:00) Cuiaba",//rsc string 1120
	"",//rsc string 1121
	"",//rsc string 1122
	"",//rsc string 1123
	"",//rsc string 1124
	"",//rsc string 1125
	"",//rsc string 1126
	"",//rsc string 1127
	"",//rsc string 1128
	"",//rsc string 1129
	"(UTC-04:00) Georgetown, La Paz, Manaus, San Juan",//rsc string 1130
	"",//rsc string 1131
	"",//rsc string 1132
	"",//rsc string 1133
	"",//rsc string 1134
	"",//rsc string 1135
	"",//rsc string 1136
	"",//rsc string 1137
	"",//rsc string 1138
	"",//rsc string 1139
	"(UTC+12:00) Fiji",//rsc string 1140
	"",//rsc string 1141
	"",//rsc string 1142
	"",//rsc string 1143
	"",//rsc string 1144
	"",//rsc string 1145
	"",//rsc string 1146
	"",//rsc string 1147
	"",//rsc string 1148
	"",//rsc string 1149
	"(UTC-01:00) Coordinated Universal Time-01",//rsc string 1150
	"UTC-01",//rsc string 1151
	"UTC-01",//rsc string 1152
	"",//rsc string 1153
	"",//rsc string 1154
	"",//rsc string 1155
	"",//rsc string 1156
	"",//rsc string 1157
	"",//rsc string 1158
	"",//rsc string 1159
	"(UTC-02:00) Coordinated Universal Time-02",//rsc string 1160
	"UTC-02",//rsc string 1161
	"UTC-02",//rsc string 1162
	"",//rsc string 1163
	"",//rsc string 1164
	"",//rsc string 1165
	"",//rsc string 1166
	"",//rsc string 1167
	"",//rsc string 1168
	"",//rsc string 1169
	"(UTC-03:00) Coordinated Universal Time-03",//rsc string 1170
	"UTC-03",//rsc string 1171
	"UTC-03",//rsc string 1172
	"",//rsc string 1173
	"",//rsc string 1174
	"",//rsc string 1175
	"",//rsc string 1176
	"",//rsc string 1177
	"",//rsc string 1178
	"",//rsc string 1179
	"(UTC-04:00) Coordinated Universal Time-04",//rsc string 1180
	"UTC-04",//rsc string 1181
	"UTC-04",//rsc string 1182
	"",//rsc string 1183
	"",//rsc string 1184
	"",//rsc string 1185
	"",//rsc string 1186
	"",//rsc string 1187
	"",//rsc string 1188
	"",//rsc string 1189
	"(UTC-05:00) Coordinated Universal Time-05",//rsc string 1190
	"UTC-05",//rsc string 1191
	"UTC-05",//rsc string 1192
	"",//rsc string 1193
	"",//rsc string 1194
	"",//rsc string 1195
	"",//rsc string 1196
	"",//rsc string 1197
	"",//rsc string 1198
	"",//rsc string 1199
	"(UTC-06:00) Coordinated Universal Time-06",//rsc string 1200
	"UTC-06",//rsc string 1201
	"UTC-06",//rsc string 1202
	"",//rsc string 1203
	"",//rsc string 1204
	"",//rsc string 1205
	"",//rsc string 1206
	"",//rsc string 1207
	"",//rsc string 1208
	"",//rsc string 1209
	"(UTC-07:00) Coordinated Universal Time-07",//rsc string 1210
	"UTC-07",//rsc string 1211
	"UTC-07",//rsc string 1212
	"",//rsc string 1213
	"",//rsc string 1214
	"",//rsc string 1215
	"",//rsc string 1216
	"",//rsc string 1217
	"",//rsc string 1218
	"",//rsc string 1219
	"(UTC-08:00) Coordinated Universal Time-0",//rsc string 1220
	"UTC-08",//rsc string 1221
	"UTC-08",//rsc string 1222
	"",//rsc string 1223
	"",//rsc string 1224
	"",//rsc string 1225
	"",//rsc string 1226
	"",//rsc string 1227
	"",//rsc string 1228
	"",//rsc string 1229
	"(UTC-09:00) Coordinated Universal Time-09",//rsc string 1230
	"UTC-09",//rsc string 1231
	"UTC-09",//rsc string 1232
	"",//rsc string 1233
	"",//rsc string 1234
	"",//rsc string 1235
	"",//rsc string 1236
	"",//rsc string 1237
	"",//rsc string 1238
	"",//rsc string 1239
	"(UTC-10:00) Coordinated Universal Time-10",//rsc string 1240
	"UTC-10",//rsc string 1241
	"UTC-10",//rsc string 1242
	"",//rsc string 1243
	"",//rsc string 1244
	"",//rsc string 1245
	"",//rsc string 1246
	"",//rsc string 1247
	"",//rsc string 1248
	"",//rsc string 1249
	"(UTC-11:00) Coordinated Universal Time-11",//rsc string 1250
	"UTC-11",//rsc string 1251
	"UTC-11",//rsc string 1252
	"",//rsc string 1253
	"",//rsc string 1254
	"",//rsc string 1255
	"",//rsc string 1256
	"",//rsc string 1257
	"",//rsc string 1258
	"",//rsc string 1259
	"(UTC-12:00) Coordinated Universal Time-1",//rsc string 1260
	"UTC-12",//rsc string 1261
	"UTC-12",//rsc string 1262
	"",//rsc string 1263
	"",//rsc string 1264
	"",//rsc string 1265
	"",//rsc string 1266
	"",//rsc string 1267
	"",//rsc string 1268
	"",//rsc string 1269
	"(UTC+01:00) Coordinated Universal Time+01",//rsc string 1270
	"UTC+01",//rsc string 1271
	"UTC+01",//rsc string 1272
	"",//rsc string 1273
	"",//rsc string 1274
	"",//rsc string 1275
	"",//rsc string 1276
	"",//rsc string 1277
	"",//rsc string 1278
	"",//rsc string 1279
	"(UTC+02:00) Coordinated Universal Time+02",//rsc string 1280
	"UTC+02",//rsc string 1281
	"UTC+02",//rsc string 1282
	"",//rsc string 1283
	"",//rsc string 1284
	"",//rsc string 1285
	"",//rsc string 1286
	"",//rsc string 1287
	"",//rsc string 1288
	"",//rsc string 1289
	"(UTC+03:00) Coordinated Universal Time+03",//rsc string 1290
	"UTC+03",//rsc string 1291
	"UTC+03",//rsc string 1292
	"",//rsc string 1293
	"",//rsc string 1294
	"",//rsc string 1295
	"",//rsc string 1296
	"",//rsc string 1297
	"",//rsc string 1298
	"",//rsc string 1299
	"(UTC+04:00) Coordinated Universal Time+04",//rsc string 1300
	"UTC+04",//rsc string 1301
	"UTC+04",//rsc string 1302
	"",//rsc string 1303
	"",//rsc string 1304
	"",//rsc string 1305
	"",//rsc string 1306
	"",//rsc string 1307
	"",//rsc string 1308
	"",//rsc string 1309
	"(UTC+05:00) Coordinated Universal Time+05",//rsc string 1310
	"UTC+05",//rsc string 1311
	"UTC+05",//rsc string 1312
	"",//rsc string 1313
	"",//rsc string 1314
	"",//rsc string 1315
	"",//rsc string 1316
	"",//rsc string 1317
	"",//rsc string 1318
	"",//rsc string 1319
	"(UTC+06:00) Coordinated Universal Time+06",//rsc string 1320
	"UTC+06",//rsc string 1321
	"UTC+06",//rsc string 1322
	"",//rsc string 1323
	"",//rsc string 1324
	"",//rsc string 1325
	"",//rsc string 1326
	"",//rsc string 1327
	"",//rsc string 1328
	"",//rsc string 1329
	"(UTC+07:00) Coordinated Universal Time+07",//rsc string 1330
	"UTC+07",//rsc string 1331
	"UTC+07",//rsc string 1332
	"",//rsc string 1333
	"",//rsc string 1334
	"",//rsc string 1335
	"",//rsc string 1336
	"",//rsc string 1337
	"",//rsc string 1338
	"",//rsc string 1339
	"(UTC+08:00) Coordinated Universal Time+08",//rsc string 1340
	"UTC+08",//rsc string 1341
	"UTC+08",//rsc string 1342
	"",//rsc string 1343
	"",//rsc string 1344
	"",//rsc string 1345
	"",//rsc string 1346
	"",//rsc string 1347
	"",//rsc string 1348
	"",//rsc string 1349
	"(UTC+09:00) Coordinated Universal Time+09",//rsc string 1350
	"UTC+09",//rsc string 1351
	"UTC+09",//rsc string 1352
	"",//rsc string 1353
	"",//rsc string 1354
	"",//rsc string 1355
	"",//rsc string 1356
	"",//rsc string 1357
	"",//rsc string 1358
	"",//rsc string 1359
	"(UTC+10:00) Coordinated Universal Time+10",//rsc string 1360
	"UTC+10",//rsc string 1361
	"UTC+10",//rsc string 1362
	"",//rsc string 1363
	"",//rsc string 1364
	"",//rsc string 1365
	"",//rsc string 1366
	"",//rsc string 1367
	"",//rsc string 1368
	"",//rsc string 1369
	"(UTC+11:00) Coordinated Universal Time+11",//rsc string 1370
	"UTC+11",//rsc string 1371
	"UTC+11",//rsc string 1372
	"",//rsc string 1373
	"",//rsc string 1374
	"",//rsc string 1375
	"",//rsc string 1376
	"",//rsc string 1377
	"",//rsc string 1378
	"",//rsc string 1379
	"(UTC+12:00) Coordinated Universal Time+12",//rsc string 1380
	"UTC+12",//rsc string 1381
	"UTC+12",//rsc string 1382
	"",//rsc string 1383
	"",//rsc string 1384
	"",//rsc string 1385
	"",//rsc string 1386
	"",//rsc string 1387
	"",//rsc string 1388
	"",//rsc string 1389
	"(UTC+13:00) Coordinated Universal Time+13",//rsc string 1390
	"UTC+13",//rsc string 1391
	"UTC+13",//rsc string 1392
	"",//rsc string 1393
	"",//rsc string 1394
	"",//rsc string 1395
	"",//rsc string 1396
	"",//rsc string 1397
	"",//rsc string 1398
	"",//rsc string 1399
	"",//rsc string 1400
	"",//rsc string 1401
	"",//rsc string 1402
	"",//rsc string 1403
	"",//rsc string 1404
	"",//rsc string 1405
	"",//rsc string 1406
	"",//rsc string 1407
	"",//rsc string 1408
	"",//rsc string 1409
	"(UTC+02:00) Damascus",//rsc string 1410
	"Syria Daylight Time",//rsc string 1411
	"Syria Standard Time",//rsc string 1412
	"",//rsc string 1413
	"",//rsc string 1414
	"",//rsc string 1415
	"",//rsc string 1416
	"",//rsc string 1417
	"",//rsc string 1418
	"",//rsc string 1419
	"(UTC+12:00) Petropavlovsk-Kamchatsky - Old",//rsc string 1420
	"",//rsc string 1421
	"",//rsc string 1422
	"",//rsc string 1423
	"",//rsc string 1424
	"",//rsc string 1425
	"",//rsc string 1426
	"",//rsc string 1427
	"",//rsc string 1428
	"",//rsc string 1429
	"",//rsc string 1430
	"",//rsc string 1431
	"",//rsc string 1432
	"",//rsc string 1433
	"",//rsc string 1434
	"",//rsc string 1435
	"",//rsc string 1436
	"",//rsc string 1437
	"",//rsc string 1438
	"",//rsc string 1439
	"(UTC+01:00) Windhoek",//rsc string 1440
	"",//rsc string 1441
	"",//rsc string 1442
	"",//rsc string 1443
	"",//rsc string 1444
	"",//rsc string 1445
	"",//rsc string 1446
	"",//rsc string 1447
	"",//rsc string 1448
	"",//rsc string 1449
	"",//rsc string 1450
	"",//rsc string 1451
	"",//rsc string 1452
	"",//rsc string 1453
	"",//rsc string 1454
	"",//rsc string 1455
	"",//rsc string 1456
	"",//rsc string 1457
	"",//rsc string 1458
	"",//rsc string 1459
	"(UTC+11:00) Solomon Is., New Caledonia",//rsc string 1460
	"",//rsc string 1461
	"",//rsc string 1462
	"",//rsc string 1463
	"",//rsc string 1464
	"",//rsc string 1465
	"",//rsc string 1466
	"",//rsc string 1467
	"",//rsc string 1468
	"",//rsc string 1469
	"(UTC+11:00) Magadan",//rsc string 1470
	"Magadan Daylight Time",//rsc string 1471
	"Magadan Standard Time",//rsc string 1472
	"",//rsc string 1473
	"",//rsc string 1474
	"",//rsc string 1475
	"",//rsc string 1476
	"",//rsc string 1477
	"",//rsc string 1478
	"",//rsc string 1479
	"",//rsc string 1480
	"",//rsc string 1481
	"",//rsc string 1482
	"",//rsc string 1483
	"",//rsc string 1484
	"",//rsc string 1485
	"",//rsc string 1486
	"",//rsc string 1487
	"",//rsc string 1488
	"",//rsc string 1489
	"(UTC+02:00) Athens, Bucharest",//rsc string 1490
	"",//rsc string 1491
	"",//rsc string 1492
	"",//rsc string 1493
	"",//rsc string 1494
	"",//rsc string 1495
	"",//rsc string 1496
	"",//rsc string 1497
	"",//rsc string 1498
	"",//rsc string 1499
	"(UTC+02:00) Istanbul",//rsc string 1500
	"Turkey Daylight Time",//rsc string 1501
	"Turkey Standard Time",//rsc string 1502
	"",//rsc string 1503
	"",//rsc string 1504
	"",//rsc string 1505
	"",//rsc string 1506
	"",//rsc string 1507
	"",//rsc string 1508
	"",//rsc string 1509
	"",//rsc string 1510
	"",//rsc string 1511
	"",//rsc string 1512
	"",//rsc string 1513
	"",//rsc string 1514
	"",//rsc string 1515
	"",//rsc string 1516
	"",//rsc string 1517
	"",//rsc string 1518
	"",//rsc string 1519
	"(UTC+04:00) Moscow, St. Petersburg, Volgograd",//rsc string 1520
	"",//rsc string 1521
	"",//rsc string 1522
	"",//rsc string 1523
	"",//rsc string 1524
	"",//rsc string 1525
	"",//rsc string 1526
	"",//rsc string 1527
	"",//rsc string 1528
	"",//rsc string 1529
	"(UTC+06:00) Ekaterinburg",//rsc string 1530
	"",//rsc string 1531
	"",//rsc string 1532
	"",//rsc string 1533
	"",//rsc string 1534
	"",//rsc string 1535
	"",//rsc string 1536
	"",//rsc string 1537
	"",//rsc string 1538
	"",//rsc string 1539
	"(UTC+07:00) Novosibirsk",//rsc string 1540
	"",//rsc string 1541
	"",//rsc string 1542
	"",//rsc string 1543
	"",//rsc string 1544
	"",//rsc string 1545
	"",//rsc string 1546
	"",//rsc string 1547
	"",//rsc string 1548
	"",//rsc string 1549
	"(UTC+08:00) Krasnoyarsk",//rsc string 1550
	"",//rsc string 1551
	"",//rsc string 1552
	"",//rsc string 1553
	"",//rsc string 1554
	"",//rsc string 1555
	"",//rsc string 1556
	"",//rsc string 1557
	"",//rsc string 1558
	"",//rsc string 1559
	"(UTC+09:00) Irkutsk",//rsc string 1560
	"",//rsc string 1561
	"",//rsc string 1562
	"",//rsc string 1563
	"",//rsc string 1564
	"",//rsc string 1565
	"",//rsc string 1566
	"",//rsc string 1567
	"",//rsc string 1568
	"",//rsc string 1569
	"(UTC+10:00) Yakutsk",//rsc string 1570
	"",//rsc string 1571
	"",//rsc string 1572
	"",//rsc string 1573
	"",//rsc string 1574
	"",//rsc string 1575
	"",//rsc string 1576
	"",//rsc string 1577
	"",//rsc string 1578
	"",//rsc string 1579
	"(UTC+11:00) Vladivostok",//rsc string 1580
	"",//rsc string 1581
	"",//rsc string 1582
	"",//rsc string 1583
	"",//rsc string 1584
	"",//rsc string 1585
	"",//rsc string 1586
	"",//rsc string 1587
	"",//rsc string 1588
	"",//rsc string 1589
	"(UTC+12:00) Magadan",//rsc string 1590
	"",//rsc string 1591
	"",//rsc string 1592
	"",//rsc string 1593
	"",//rsc string 1594
	"",//rsc string 1595
	"",//rsc string 1596
	"",//rsc string 1597
	"",//rsc string 1598
	"",//rsc string 1599
	"(UTC+03:00) Kaliningrad",//rsc string 1600
	"Kaliningrad Daylight Time",//rsc string 1601
	"Kaliningrad Standard Time",//rsc string 1602
	"",//rsc string 1603
	"",//rsc string 1604
	"",//rsc string 1605
	"",//rsc string 1606
	"",//rsc string 1607
	"",//rsc string 1608
	"",//rsc string 1609
	"",//rsc string 1610
	"",//rsc string 1611
	"",//rsc string 1612
	"",//rsc string 1613
	"",//rsc string 1614
	"",//rsc string 1615
	"",//rsc string 1616
	"",//rsc string 1617
	"",//rsc string 1618
	"",//rsc string 1619
	"(UTC+03:00) Kaliningrad, Minsk",//rsc string 1620
	"",//rsc string 1621
	"",//rsc string 1622
	"",//rsc string 1623
	"",//rsc string 1624
	"",//rsc string 1625
	"",//rsc string 1626
	"",//rsc string 1627
	"",//rsc string 1628
	"",//rsc string 1629
	"(UTC+02:00) Nicosia",//rsc string 1630
	"",//rsc string 1631
	"",//rsc string 1632
	"",//rsc string 1633
	"",//rsc string 1634
	"",//rsc string 1635
	"",//rsc string 1636
	"",//rsc string 1637
	"",//rsc string 1638
	"",//rsc string 1639
	"(UTC+13:00) Samoa",//rsc string 1640
	"",//rsc string 1641
	"",//rsc string 1642
	"",//rsc string 1643
	"",//rsc string 1644
	"",//rsc string 1645
	"",//rsc string 1646
	"",//rsc string 1647
	"",//rsc string 1648
	"",//rsc string 1649
	"",//rsc string 1650
	"",//rsc string 1651
	"",//rsc string 1652
	"",//rsc string 1653
	"",//rsc string 1654
	"",//rsc string 1655
	"",//rsc string 1656
	"",//rsc string 1657
	"",//rsc string 1658
	"",//rsc string 1659
	"(UTC-03:00) Salvador",//rsc string 1660
	"Bahia Daylight Time",//rsc string 1661
	"Bahia Standard Time",//rsc string 1662
	"",//rsc string 1663
	"",//rsc string 1664
	"",//rsc string 1665
	"",//rsc string 1666
	"",//rsc string 1667
	"",//rsc string 1668
	"",//rsc string 1669
	"",//rsc string 1670
	"",//rsc string 1671
	"",//rsc string 1672
	"",//rsc string 1673
	"",//rsc string 1674
	"",//rsc string 1675
	"",//rsc string 1676
	"",//rsc string 1677
	"",//rsc string 1678
	"",//rsc string 1679
	"(UTC+02:00) E. Europe",//rsc string 1680
	"",//rsc string 1681
	"",//rsc string 1682
	"",//rsc string 1683
	"",//rsc string 1684
	"",//rsc string 1685
	"",//rsc string 1686
	"",//rsc string 1687
	"",//rsc string 1688
	"",//rsc string 1689
	"",//rsc string 1690
	"",//rsc string 1691
	"",//rsc string 1692
	"",//rsc string 1693
	"",//rsc string 1694
	"",//rsc string 1695
	"",//rsc string 1696
	"",//rsc string 1697
	"",//rsc string 1698
	"",//rsc string 1699
	"(UTC+03:00) Amman",//rsc string 1700
	"",//rsc string 1701
	"",//rsc string 1702
	"",//rsc string 1703
	"",//rsc string 1704
	"",//rsc string 1705
	"",//rsc string 1706
	"",//rsc string 1707
	"",//rsc string 1708
	"",//rsc string 1709
	"",//rsc string 1710
	"",//rsc string 1711
	"",//rsc string 1712
	"",//rsc string 1713
	"",//rsc string 1714
	"",//rsc string 1715
	"",//rsc string 1716
	"",//rsc string 1717
	"",//rsc string 1718
	"",//rsc string 1719
	"(UTC+02:00) Tripoli",//rsc string 1720
	"Libya Daylight Time",//rsc string 1721
	"Libya Standard Time",//rsc string 1722
	"",//rsc string 1723
	"",//rsc string 1724
	"",//rsc string 1725
	"",//rsc string 1726
	"",//rsc string 1727
	"",//rsc string 1728
	"",//rsc string 1729
	"",//rsc string 1730
	"",//rsc string 1731
	"",//rsc string 1732
	"",//rsc string 1733
	"",//rsc string 1734
	"",//rsc string 1735
	"",//rsc string 1736
	"",//rsc string 1737
	"",//rsc string 1738
	"",//rsc string 1739
	"(UTC+05:00) Ashgabat, Tashkent",//rsc string 1740
	"",//rsc string 1741
	"",//rsc string 1742
	"",//rsc string 1743
	"",//rsc string 1744
	"",//rsc string 1745
	"",//rsc string 1746
	"",//rsc string 1747
	"",//rsc string 1748
	"",//rsc string 1749
	"",//rsc string 1750
	"",//rsc string 1751
	"",//rsc string 1752
	"",//rsc string 1753
	"",//rsc string 1754
	"",//rsc string 1755
	"",//rsc string 1756
	"",//rsc string 1757
	"",//rsc string 1758
	"",//rsc string 1759
	"(UTC-02:00) Mid-Atlantic - Old",//rsc string 1760
	"",//rsc string 1761
	"",//rsc string 1762
	"",//rsc string 1763
	"",//rsc string 1764
	"",//rsc string 1765
	"",//rsc string 1766
	"",//rsc string 1767
	"",//rsc string 1768
	"",//rsc string 1769
	"",//rsc string 1770
	"",//rsc string 1771
	"",//rsc string 1772
	"",//rsc string 1773
	"",//rsc string 1774
	"",//rsc string 1775
	"",//rsc string 1776
	"",//rsc string 1777
	"",//rsc string 1778
	"",//rsc string 1779
	"(UTC+02:00) Tripoli",//rsc string 1780
	"",//rsc string 1781
	"",//rsc string 1782
	"",//rsc string 1783
	"",//rsc string 1784
	"",//rsc string 1785
	"",//rsc string 1786
	"",//rsc string 1787
	"",//rsc string 1788
	"",//rsc string 1789
	"",//rsc string 1790
	"",//rsc string 1791
	"",//rsc string 1792
	"",//rsc string 1793
	"",//rsc string 1794
	"",//rsc string 1795
	"",//rsc string 1796
	"",//rsc string 1797
	"",//rsc string 1798
	"",//rsc string 1799
	"(UTC+14:00) Kiritimati Island",//rsc string 1800
	"Line Islands Daylight Time",//rsc string 1801
	"Line Islands Standard Time",//rsc string 1802
	"",//rsc string 1803
	"",//rsc string 1804
	"",//rsc string 1805
	"",//rsc string 1806
	"",//rsc string 1807
	"",//rsc string 1808
	"",//rsc string 1809
	"",//rsc string 1810
	"",//rsc string 1811
	"",//rsc string 1812
	"",//rsc string 1813
	"",//rsc string 1814
	"",//rsc string 1815
	"",//rsc string 1816
	"",//rsc string 1817
	"",//rsc string 1818
	"",//rsc string 1819
	"(UTC+02:00) Kaliningrad (RTZ 1)",//rsc string 1820
	"Russia TZ 1 Daylight Time",//rsc string 1821
	"Russia TZ 1 Standard Time",//rsc string 1822
	"",//rsc string 1823
	"",//rsc string 1824
	"",//rsc string 1825
	"",//rsc string 1826
	"",//rsc string 1827
	"",//rsc string 1828
	"",//rsc string 1829
	"(UTC+03:00) Moscow, St. Petersburg, Volgograd (RTZ 2)",//rsc string 1830
	"Russia TZ 2 Daylight Time",//rsc string 1831
	"Russia TZ 2 Standard Time",//rsc string 1832
	"",//rsc string 1833
	"",//rsc string 1834
	"",//rsc string 1835
	"",//rsc string 1836
	"",//rsc string 1837
	"",//rsc string 1838
	"",//rsc string 1839
	"(UTC+05:00) Ekaterinburg (RTZ 4)",//rsc string 1840
	"Russia TZ 4 Daylight Time",//rsc string 1841
	"Russia TZ 4 Standard Time",//rsc string 1842
	"",//rsc string 1843
	"",//rsc string 1844
	"",//rsc string 1845
	"",//rsc string 1846
	"",//rsc string 1847
	"",//rsc string 1848
	"",//rsc string 1849
	"(UTC+06:00) Novosibirsk (RTZ 5)",//rsc string 1850
	"Russia TZ 5 Daylight Time",//rsc string 1851
	"Russia TZ 5 Standard Time",//rsc string 1852
	"",//rsc string 1853
	"",//rsc string 1854
	"",//rsc string 1855
	"",//rsc string 1856
	"",//rsc string 1857
	"",//rsc string 1858
	"",//rsc string 1859
	"(UTC+07:00) Krasnoyarsk (RTZ 6)",//rsc string 1860
	"Russia TZ 6 Daylight Time",//rsc string 1861
	"Russia TZ 6 Standard Time",//rsc string 1862
	"",//rsc string 1863
	"",//rsc string 1864
	"",//rsc string 1865
	"",//rsc string 1866
	"",//rsc string 1867
	"",//rsc string 1868
	"",//rsc string 1869
	"(UTC+08:00) Irkutsk (RTZ 7)",//rsc string 1870
	"Russia TZ 7 Daylight Time",//rsc string 1871
	"Russia TZ 7 Standard Time",//rsc string 1872
	"",//rsc string 1873
	"",//rsc string 1874
	"",//rsc string 1875
	"",//rsc string 1876
	"",//rsc string 1877
	"",//rsc string 1878
	"",//rsc string 1879
	"(UTC+09:00) Yakutsk (RTZ 8)",//rsc string 1880
	"Russia TZ 8 Daylight Time",//rsc string 1881
	"Russia TZ 8 Standard Time",//rsc string 1882
	"",//rsc string 1883
	"",//rsc string 1884
	"",//rsc string 1885
	"",//rsc string 1886
	"",//rsc string 1887
	"",//rsc string 1888
	"",//rsc string 1889
	"(UTC+04:00) Izhevsk, Samara (RTZ 3)",//rsc string 1890
	"Russia TZ 3 Daylight Time",//rsc string 1891
	"Russia TZ 3 Standard Time",//rsc string 1892
	"",//rsc string 1893
	"",//rsc string 1894
	"",//rsc string 1895
	"",//rsc string 1896
	"",//rsc string 1897
	"",//rsc string 1898
	"",//rsc string 1899
	"",//rsc string 1900
	"",//rsc string 1901
	"",//rsc string 1902
	"",//rsc string 1903
	"",//rsc string 1904
	"",//rsc string 1905
	"",//rsc string 1906
	"",//rsc string 1907
	"",//rsc string 1908
	"",//rsc string 1909
	"(UTC+11:00) Chokurdakh (RTZ 10)",//rsc string 1910
	"Russia TZ 10 Daylight Time",//rsc string 1911
	"Russia TZ 10 Standard Time",//rsc string 1912
	"",//rsc string 1913
	"",//rsc string 1914
	"",//rsc string 1915
	"",//rsc string 1916
	"",//rsc string 1917
	"",//rsc string 1918
	"",//rsc string 1919
	"",//rsc string 1920
	"",//rsc string 1921
	"",//rsc string 1922
	"",//rsc string 1923
	"",//rsc string 1924
	"",//rsc string 1925
	"",//rsc string 1926
	"",//rsc string 1927
	"",//rsc string 1928
	"",//rsc string 1929
	"(UTC+12:00) Anadyr, Petropavlovsk-Kamchatsky (RTZ 11)",//rsc string 1930
	"Russia TZ 11 Daylight Time",//rsc string 1931
	"Russia TZ 11 Standard Time",//rsc string 1932
	"",//rsc string 1933
	"",//rsc string 1934
	"",//rsc string 1935
	"",//rsc string 1936
	"",//rsc string 1937
	"",//rsc string 1938
	"",//rsc string 1939
	"",//rsc string 1940
	"",//rsc string 1941
	"",//rsc string 1942
	"",//rsc string 1943
	"",//rsc string 1944
	"",//rsc string 1945
	"",//rsc string 1946
	"",//rsc string 1947
	"",//rsc string 1948
	"",//rsc string 1949
	"(UTC+10:00) Vladivostok, Magadan (RTZ 9)",//rsc string 1950
	"Russia TZ 9 Daylight Time",//rsc string 1951
	"Russia TZ 9 Standard Time",//rsc string 1952
	"",//rsc string 1953
	"",//rsc string 1954
	"",//rsc string 1955
	"",//rsc string 1956
	"",//rsc string 1957
	"",//rsc string 1958
	"",//rsc string 1959
	"",//rsc string 1960
	"",//rsc string 1961
	"",//rsc string 1962
	"",//rsc string 1963
	"",//rsc string 1964
	"",//rsc string 1965
	"",//rsc string 1966
	"",//rsc string 1967
	"",//rsc string 1968
	"",//rsc string 1969
	"(UTC+03:00) Minsk",//rsc string 1970
	"Belarus Daylight Time",//rsc string 1971
	"Belarus Standard Time",//rsc string 1972
	"",//rsc string 1973
	"",//rsc string 1974
	"",//rsc string 1975
	"",//rsc string 1976
	"",//rsc string 1977
	"",//rsc string 1978
	"",//rsc string 1979
	"(UTC+10:00) Magadan",//rsc string 1980
	"",//rsc string 1981
	"",//rsc string 1982
	"",//rsc string 1983
	"",//rsc string 1984
	"",//rsc string 1985
	"",//rsc string 1986
	"",//rsc string 1987
	"",//rsc string 1988
	"",//rsc string 1989
	"",//rsc string 1990
	"",//rsc string 1991
	"",//rsc string 1992
	"",//rsc string 1993
	"",//rsc string 1994
	"",//rsc string 1995
	"",//rsc string 1996
	"",//rsc string 1997
	"",//rsc string 1998
	"",//rsc string 1999
	"(UTC-01:00) Cabo Verde Is.",//rsc string 2000
	"Cabo Verde Daylight Time",//rsc string 2001
	"Cabo Verde Standard Time",//rsc string 2002
	"",//rsc string 2003
	"",//rsc string 2004
	"",//rsc string 2005
	"",//rsc string 2006
	"",//rsc string 2007
	"",//rsc string 2008
	"",//rsc string 2009
	"",//rsc string 2011
	"",//rsc string 2012
	"",//rsc string 2013
	"",//rsc string 2014
	"",//rsc string 2015
	"",//rsc string 2016
	"",//rsc string 2017
	"",//rsc string 2018
	"",//rsc string 2019
	"(UTC-03:00) Santiago",//rsc string 2020
	"",//rsc string 2021
	"",//rsc string 2022
	"",//rsc string 2023
	"",//rsc string 2024
	"",//rsc string 2025
	"",//rsc string 2026
	"",//rsc string 2027
	"",//rsc string 2028
	"",//rsc string 2029
	"",//rsc string 2030
	"",//rsc string 2031
	"",//rsc string 2032
	"",//rsc string 2033
	"",//rsc string 2034
	"",//rsc string 2035
	"",//rsc string 2036
	"",//rsc string 2037
	"",//rsc string 2038
	"",//rsc string 2039
	"(UTC-05:00) Chetumal",//rsc string 2040
	"Eastern Daylight Time (Mexico)",//rsc string 2041
	"Eastern Standard Time (Mexico)",//rsc string 2042
	"",//rsc string 2043
	"",//rsc string 2044
	"",//rsc string 2045
	"",//rsc string 2046
	"",//rsc string 2047
	"",//rsc string 2048
	"",//rsc string 2049
	"",//rsc string 2050
	"",//rsc string 2051
	"",//rsc string 2052
	"",//rsc string 2053
	"",//rsc string 2054
	"",//rsc string 2055
	"",//rsc string 2056
	"",//rsc string 2057
	"",//rsc string 2058
	"",//rsc string 2059
	"(UTC+08:30) Pyongyang",//rsc string 2060
	"North Korea Daylight Time",//rsc string 2061
	"North Korea Standard Time",//rsc string 2062
	"",//rsc string 2063
	"",//rsc string 2064
	"",//rsc string 2065
	"",//rsc string 2066
	"",//rsc string 2067
	"",//rsc string 2068
	"",//rsc string 2069
	"",//rsc string 2070
	"",//rsc string 2071
	"",//rsc string 2072
	"",//rsc string 2073
	"",//rsc string 2074
	"",//rsc string 2075
	"",//rsc string 2076
	"",//rsc string 2077
	"",//rsc string 2078
	"",//rsc string 2079
	"(UTC-03:00) City of Buenos Aires",//rsc string 2080
	"",//rsc string 2081
	"",//rsc string 2082
	"",//rsc string 2083
	"",//rsc string 2084
	"",//rsc string 2085
	"",//rsc string 2086
	"",//rsc string 2087
	"",//rsc string 2088
	"",//rsc string 2089
	"",//rsc string 2090
	"",//rsc string 2091
	"",//rsc string 2092
	"",//rsc string 2093
	"",//rsc string 2094
	"",//rsc string 2095
	"",//rsc string 2096
	"",//rsc string 2097
	"",//rsc string 2098
	"",//rsc string 2099
	"",//rsc string 2100
	"",//rsc string 2101
	"",//rsc string 2102
	"",//rsc string 2103
	"",//rsc string 2104
	"",//rsc string 2105
	"",//rsc string 2106
	"",//rsc string 2107
	"",//rsc string 2108
	"",//rsc string 2109
	"",//rsc string 2110
	"",//rsc string 2111
	"",//rsc string 2112
	"",//rsc string 2113
	"",//rsc string 2114
	"",//rsc string 2115
	"",//rsc string 2116
	"",//rsc string 2117
	"",//rsc string 2118
	"",//rsc string 2119
	"(UTC+10:00) Vladivostok",//rsc string 2120
	"",//rsc string 2121
	"",//rsc string 2122
	"",//rsc string 2123
	"",//rsc string 2124
	"",//rsc string 2125
	"",//rsc string 2126
	"",//rsc string 2127
	"",//rsc string 2128
	"",//rsc string 2129
	"",//rsc string 2130
	"",//rsc string 2131
	"",//rsc string 2132
	"",//rsc string 2133
	"",//rsc string 2134
	"",//rsc string 2135
	"",//rsc string 2136
	"",//rsc string 2137
	"",//rsc string 2138
	"",//rsc string 2139
	"(UTC+09:00) Chita",//rsc string 2140
	"Transbaikal Daylight Time",//rsc string 2141
	"Transbaikal Standard Time",//rsc string 2142
	"",//rsc string 2143
	"",//rsc string 2144
	"",//rsc string 2145
	"",//rsc string 2146
	"",//rsc string 2147
	"",//rsc string 2148
	"",//rsc string 2149
	"",//rsc string 2150
	"",//rsc string 2151
	"",//rsc string 2152
	"",//rsc string 2153
	"",//rsc string 2154
	"",//rsc string 2155
	"",//rsc string 2156
	"",//rsc string 2157
	"",//rsc string 2158
	"",//rsc string 2159
	"(UTC+07:00) Barnaul, Gorno-Altaysk",//rsc string 2160
	"Altai Daylight Time",//rsc string 2161
	"Altai Standard Time",//rsc string 2162
	"",//rsc string 2163
	"",//rsc string 2164
	"",//rsc string 2165
	"",//rsc string 2166
	"",//rsc string 2167
	"",//rsc string 2168
	"",//rsc string 2169
	"",//rsc string 2170
	"",//rsc string 2171
	"",//rsc string 2172
	"",//rsc string 2173
	"",//rsc string 2174
	"",//rsc string 2175
	"",//rsc string 2176
	"",//rsc string 2177
	"",//rsc string 2178
	"",//rsc string 2179
	"(UTC+04:00) Astrakhan, Ulyanovsk",//rsc string 2180
	"Astrakhan Daylight Time",//rsc string 2181
	"Astrakhan Standard Time",//rsc string 2182
	"",//rsc string 2183
	"",//rsc string 2184
	"",//rsc string 2185
	"",//rsc string 2186
	"",//rsc string 2187
	"",//rsc string 2188
	"",//rsc string 2189
	"(UTC+05:00) Ekaterinburg",//rsc string 2190
	"",//rsc string 2191
	"",//rsc string 2192
	"",//rsc string 2193
	"",//rsc string 2194
	"",//rsc string 2195
	"",//rsc string 2196
	"",//rsc string 2197
	"",//rsc string 2198
	"",//rsc string 2199
	"(UTC+02:00) Kaliningrad",//rsc string 2200
	"",//rsc string 2201
	"",//rsc string 2202
	"",//rsc string 2203
	"",//rsc string 2204
	"",//rsc string 2205
	"",//rsc string 2206
	"",//rsc string 2207
	"",//rsc string 2208
	"",//rsc string 2209
	"",//rsc string 2210
	"",//rsc string 2211
	"",//rsc string 2212
	"",//rsc string 2213
	"",//rsc string 2214
	"",//rsc string 2215
	"",//rsc string 2216
	"",//rsc string 2217
	"",//rsc string 2218
	"",//rsc string 2219
	"(UTC+06:00) Novosibirsk",//rsc string 2220
	"",//rsc string 2221
	"",//rsc string 2222
	"",//rsc string 2223
	"",//rsc string 2224
	"",//rsc string 2225
	"",//rsc string 2226
	"",//rsc string 2227
	"",//rsc string 2228
	"",//rsc string 2229
	"(UTC+08:00) Irkutsk",//rsc string 2230
	"",//rsc string 2231
	"",//rsc string 2232
	"",//rsc string 2233
	"",//rsc string 2234
	"",//rsc string 2235
	"",//rsc string 2236
	"",//rsc string 2237
	"",//rsc string 2238
	"",//rsc string 2239
	"(UTC+07:00) Krasnoyarsk",//rsc string 2240
	"",//rsc string 2241
	"",//rsc string 2242
	"",//rsc string 2243
	"",//rsc string 2244
	"",//rsc string 2245
	"",//rsc string 2246
	"",//rsc string 2247
	"",//rsc string 2248
	"",//rsc string 2249
	"(UTC+11:00) Chokurdakh",//rsc string 2250
	"",//rsc string 2251
	"",//rsc string 2252
	"",//rsc string 2253
	"",//rsc string 2254
	"",//rsc string 2255
	"",//rsc string 2256
	"",//rsc string 2257
	"",//rsc string 2258
	"",//rsc string 2259
	"(UTC+12:00) Anadyr, Petropavlovsk-Kamchatsky",//rsc string 2260
	"",//rsc string 2261
	"",//rsc string 2262
	"",//rsc string 2263
	"",//rsc string 2264
	"",//rsc string 2265
	"",//rsc string 2266
	"",//rsc string 2267
	"",//rsc string 2268
	"",//rsc string 2269
	"(UTC+04:00) Izhevsk, Samara",//rsc string 2270
	"",//rsc string 2271
	"",//rsc string 2272
	"",//rsc string 2273
	"",//rsc string 2274
	"",//rsc string 2275
	"",//rsc string 2276
	"",//rsc string 2277
	"",//rsc string 2278
	"",//rsc string 2279
	"(UTC+03:00) Moscow, St. Petersburg, Volgograd",//rsc string 2280
	"",//rsc string 2281
	"",//rsc string 2282
	"",//rsc string 2283
	"",//rsc string 2284
	"",//rsc string 2285
	"",//rsc string 2286
	"",//rsc string 2287
	"",//rsc string 2288
	"",//rsc string 2289
	"(UTC+09:00) Yakutsk",//rsc string 2290
	"",//rsc string 2291
	"",//rsc string 2292
	"",//rsc string 2293
	"",//rsc string 2294
	"",//rsc string 2295
	"",//rsc string 2296
	"",//rsc string 2297
	"",//rsc string 2298
	"",//rsc string 2299
	"",//rsc string 2300
	"",//rsc string 2301
	"",//rsc string 2302
	"",//rsc string 2303
	"",//rsc string 2304
	"",//rsc string 2305
	"",//rsc string 2306
	"",//rsc string 2307
	"",//rsc string 2308
	"",//rsc string 2309
	"(UTC+11:00) Magadan, Sakhalin",//rsc string 2310
	"",//rsc string 2311
	"",//rsc string 2312
	"",//rsc string 2313
	"",//rsc string 2314
	"",//rsc string 2315
	"",//rsc string 2316
	"",//rsc string 2317
	"",//rsc string 2318
	"",//rsc string 2319
	"(UTC+11:00) Sakhalin",//rsc string 2320
	"Sakhalin Daylight Time",//rsc string 2321
	"Sakhalin Standard Time",//rsc string 2322
	"",//rsc string 2323
	"",//rsc string 2324
	"",//rsc string 2325
	"",//rsc string 2326
	"",//rsc string 2327
	"",//rsc string 2328
	"",//rsc string 2329
	"",//rsc string 2330
	"",//rsc string 2331
	"",//rsc string 2332
	"",//rsc string 2333
	"",//rsc string 2334
	"",//rsc string 2335
	"",//rsc string 2336
	"",//rsc string 2337
	"",//rsc string 2338
	"",//rsc string 2339
	"(UTC-05:00) Haiti",//rsc string 2340
	"Haiti Daylight Time",//rsc string 2341
	"Haiti Standard Time",//rsc string 2342
	"",//rsc string 2343
	"",//rsc string 2344
	"",//rsc string 2345
	"",//rsc string 2346
	"",//rsc string 2347
	"",//rsc string 2348
	"",//rsc string 2349
	"",//rsc string 2350
	"",//rsc string 2351
	"",//rsc string 2352
	"",//rsc string 2353
	"",//rsc string 2354
	"",//rsc string 2355
	"",//rsc string 2356
	"",//rsc string 2357
	"",//rsc string 2358
	"",//rsc string 2359
	"",//rsc string 2360
	"",//rsc string 2361
	"",//rsc string 2362
	"",//rsc string 2363
	"",//rsc string 2364
	"",//rsc string 2365
	"",//rsc string 2366
	"",//rsc string 2367
	"",//rsc string 2368
	"",//rsc string 2369
	"(UTC-06:00) Easter Island",//rsc string 2370
	"Easter Island Daylight Time",//rsc string 2371
	"Easter Island Standard Time",//rsc string 2372
	"",//rsc string 2373
	"",//rsc string 2374
	"",//rsc string 2375
	"",//rsc string 2376
	"",//rsc string 2377
	"",//rsc string 2378
	"",//rsc string 2379
	"",//rsc string 2380
	"",//rsc string 2381
	"",//rsc string 2382
	"",//rsc string 2383
	"",//rsc string 2384
	"",//rsc string 2385
	"",//rsc string 2386
	"",//rsc string 2387
	"",//rsc string 2388
	"",//rsc string 2389
	"(UTC-10:00) Aleutian Islands",//rsc string 2390
	"Aleutian Daylight Time",//rsc string 2391
	"Aleutian Standard Time",//rsc string 2392
	"",//rsc string 2393
	"",//rsc string 2394
	"",//rsc string 2395
	"",//rsc string 2396
	"",//rsc string 2397
	"",//rsc string 2398
	"",//rsc string 2399
	"",//rsc string 2400
	"",//rsc string 2401
	"",//rsc string 2402
	"",//rsc string 2403
	"",//rsc string 2404
	"",//rsc string 2405
	"",//rsc string 2406
	"",//rsc string 2407
	"",//rsc string 2408
	"",//rsc string 2409
	"(UTC-09:30) Marquesas Islands",//rsc string 2410
	"Marquesas Daylight Time",//rsc string 2411
	"Marquesas Standard Time",//rsc string 2412
	"",//rsc string 2413
	"",//rsc string 2414
	"",//rsc string 2415
	"",//rsc string 2416
	"",//rsc string 2417
	"",//rsc string 2418
	"",//rsc string 2419
	"",//rsc string 2420
	"",//rsc string 2421
	"",//rsc string 2422
	"",//rsc string 2423
	"",//rsc string 2424
	"",//rsc string 2425
	"",//rsc string 2426
	"",//rsc string 2427
	"",//rsc string 2428
	"",//rsc string 2429
	"(UTC-05:00) Havana",//rsc string 2430
	"Cuba Daylight Time",//rsc string 2431
	"Cuba Standard Time",//rsc string 2432
	"",//rsc string 2433
	"",//rsc string 2434
	"",//rsc string 2435
	"",//rsc string 2436
	"",//rsc string 2437
	"",//rsc string 2438
	"",//rsc string 2439
	"",//rsc string 2440
	"",//rsc string 2441
	"",//rsc string 2442
	"",//rsc string 2443
	"",//rsc string 2444
	"",//rsc string 2445
	"",//rsc string 2446
	"",//rsc string 2447
	"",//rsc string 2448
	"",//rsc string 2449
	"(UTC-03:00) Saint Pierre and Miquelon",//rsc string 2450
	"Saint Pierre Daylight Time",//rsc string 2451
	"Saint Pierre Standard Time",//rsc string 2452
	"",//rsc string 2453
	"",//rsc string 2454
	"",//rsc string 2455
	"",//rsc string 2456
	"",//rsc string 2457
	"",//rsc string 2458
	"",//rsc string 2459
	"",//rsc string 2460
	"",//rsc string 2461
	"",//rsc string 2462
	"",//rsc string 2463
	"",//rsc string 2464
	"",//rsc string 2465
	"",//rsc string 2466
	"",//rsc string 2467
	"",//rsc string 2468
	"",//rsc string 2469
	"(UTC+02:00) Gaza, Hebron",//rsc string 2470
	"West Bank Gaza Daylight Time",//rsc string 2471
	"West Bank Gaza Standard Tim",//rsc string 2472
	"",//rsc string 2473
	"",//rsc string 2474
	"",//rsc string 2475
	"",//rsc string 2476
	"",//rsc string 2477
	"",//rsc string 2478
	"",//rsc string 2479
	"",//rsc string 2480
	"",//rsc string 2481
	"",//rsc string 2482
	"",//rsc string 2483
	"",//rsc string 2484
	"",//rsc string 2485
	"",//rsc string 2486
	"",//rsc string 2487
	"",//rsc string 2488
	"",//rsc string 2489
	"(UTC+08:45) Eucla",//rsc string 2490
	"Aus Central W. Daylight Time",//rsc string 2491
	"Aus Central W. Standard Time",//rsc string 2492
	"",//rsc string 2493
	"",//rsc string 2494
	"",//rsc string 2495
	"",//rsc string 2496
	"",//rsc string 2497
	"",//rsc string 2498
	"",//rsc string 2499
	"",//rsc string 2500
	"",//rsc string 2501
	"",//rsc string 2502
	"",//rsc string 2503
	"",//rsc string 2504
	"",//rsc string 2505
	"",//rsc string 2506
	"",//rsc string 2507
	"",//rsc string 2508
	"",//rsc string 2509
	"(UTC+10:30) Lord Howe Island",//rsc string 2510
	"Lord Howe Daylight Time",//rsc string 2511
	"Lord Howe Standard Time",//rsc string 2512
	"",//rsc string 2513
	"",//rsc string 2514
	"",//rsc string 2515
	"",//rsc string 2516
	"",//rsc string 2517
	"",//rsc string 2518
	"",//rsc string 2519
	"",//rsc string 2520
	"",//rsc string 2521
	"",//rsc string 2522
	"",//rsc string 2523
	"",//rsc string 2524
	"",//rsc string 2525
	"",//rsc string 2526
	"",//rsc string 2527
	"",//rsc string 2528
	"",//rsc string 2529
	"(UTC+12:45) Chatham Islands",//rsc string 2530
	"Chatham Islands Daylight Time",//rsc string 2531
	"Chatham Islands Standard Time",//rsc string 2532
	"",//rsc string 2533
	"",//rsc string 2534
	"",//rsc string 2535
	"",//rsc string 2536
	"",//rsc string 2537
	"",//rsc string 2538
	"",//rsc string 2539
	"",//rsc string 2540
	"",//rsc string 2541
	"",//rsc string 2542
	"",//rsc string 2543
	"",//rsc string 2544
	"",//rsc string 2545
	"",//rsc string 2546
	"",//rsc string 2547
	"",//rsc string 2548
	"",//rsc string 2549
	"(UTC+07:00) Hovd",//rsc string 2550
	"W. Mongolia Daylight Time",//rsc string 2551
	"W. Mongolia Standard Time",//rsc string 2552
	"",//rsc string 2553
	"",//rsc string 2554
	"",//rsc string 2555
	"",//rsc string 2556
	"",//rsc string 2557
	"",//rsc string 2558
	"",//rsc string 2559
	"",//rsc string 2560
	"",//rsc string 2561
	"",//rsc string 2562
	"",//rsc string 2563
	"",//rsc string 2564
	"",//rsc string 2565
	"",//rsc string 2566
	"",//rsc string 2567
	"",//rsc string 2568
	"",//rsc string 2569
	"(UTC-04:00) Turks and Caicos",//rsc string 2570
	"Turks and Caicos Daylight Time",//rsc string 2571
	"Turks and Caicos Standard Time",//rsc string 2572
	"",//rsc string 2573
	"",//rsc string 2574
	"",//rsc string 2575
	"",//rsc string 2576
	"",//rsc string 2577
	"",//rsc string 2578
	"",//rsc string 2579
	"",//rsc string 2580
	"",//rsc string 2581
	"",//rsc string 2582
	"",//rsc string 2583
	"",//rsc string 2584
	"",//rsc string 2585
	"",//rsc string 2586
	"",//rsc string 2587
	"",//rsc string 2588
	"",//rsc string 2589
	"UTC-03:00) Araguaina",//rsc string 2590
	"Tocantins Daylight Time",//rsc string 2591
	"Tocantins Standard Time",//rsc string 2592
	"",//rsc string 2593
	"",//rsc string 2594
	"",//rsc string 2595
	"",//rsc string 2596
	"",//rsc string 2597
	"",//rsc string 2598
	"",//rsc string 2599
	"",//rsc string 2600
	"",//rsc string 2601
	"",//rsc string 2602
	"",//rsc string 2603
	"",//rsc string 2604
	"",//rsc string 2605
	"",//rsc string 2606
	"",//rsc string 2607
	"",//rsc string 2608
	"",//rsc string 2609
	"(UTC+11:00) Bougainville Island",//rsc string 2610
	"Bougainville Daylight Time",//rsc string 2611
	"Bougainville Standard Time",//rsc string 2612
	"",//rsc string 2613
	"",//rsc string 2614
	"",//rsc string 2615
	"",//rsc string 2616
	"",//rsc string 2617
	"",//rsc string 2618
	"",//rsc string 2619
	"",//rsc string 2620
	"",//rsc string 2621
	"",//rsc string 2622
	"",//rsc string 2623
	"",//rsc string 2624
	"",//rsc string 2625
	"",//rsc string 2626
	"",//rsc string 2627
	"",//rsc string 2628
	"",//rsc string 2629
	"(UTC+11:00) Norfolk Island",//rsc string 2630
	"Norfolk Daylight Time",//rsc string 2631
	"Norfolk Standard Time",//rsc string 2632
	"",//rsc string 2633
	"",//rsc string 2634
	"",//rsc string 2635
	"",//rsc string 2636
	"",//rsc string 2637
	"",//rsc string 2638
	"",//rsc string 2639
	"",//rsc string 2640
	"",//rsc string 2641
	"",//rsc string 2642
	"",//rsc string 2643
	"",//rsc string 2644
	"",//rsc string 2645
	"",//rsc string 2646
	"",//rsc string 2647
	"",//rsc string 2648
	"",//rsc string 2649
	"(UTC+00:00) Casablanca",//rsc string 2650
	"",//rsc string 2651
	"",//rsc string 2652
	"",//rsc string 2653
	"",//rsc string 2654
	"",//rsc string 2655
	"",//rsc string 2656
	"",//rsc string 2657
	"",//rsc string 2658
	"",//rsc string 2659
	"",//rsc string 2660
	"",//rsc string 2661
	"",//rsc string 2662
	"",//rsc string 2663
	"",//rsc string 2664
	"",//rsc string 2665
	"",//rsc string 2666
	"",//rsc string 2667
	"",//rsc string 2668
	"",//rsc string 2669
	"(UTC+00:00) Dublin, Edinburgh, Lisbon, London",//rsc string 2670
	"",//rsc string 2671
	"",//rsc string 2672
	"",//rsc string 2673
	"",//rsc string 2674
	"",//rsc string 2675
	"",//rsc string 2676
	"",//rsc string 2677
	"",//rsc string 2678
	"",//rsc string 2679
	"",//rsc string 2680
	"",//rsc string 2681
	"",//rsc string 2682
	"",//rsc string 2683
	"",//rsc string 2684
	"",//rsc string 2685
	"",//rsc string 2686
	"",//rsc string 2687
	"",//rsc string 2688
	"",//rsc string 2689
	"(UTC+00:00) Monrovia, Reykjavik",//rsc string 2690
	"",//rsc string 2691
	"",//rsc string 2692
	"",//rsc string 2693
	"",//rsc string 2694
	"",//rsc string 2695
	"",//rsc string 2696
	"",//rsc string 2697
	"",//rsc string 2698
	"",//rsc string 2699
	"",//rsc string 2700
	"",//rsc string 2701
	"",//rsc string 2702
	"",//rsc string 2703
	"",//rsc string 2704
	"",//rsc string 2705
	"",//rsc string 2706
	"",//rsc string 2707
	"",//rsc string 2708
	"",//rsc string 2709
	"(UTC+02:00) Chisinau",//rsc string 2710
	"",//rsc string 2711
	"",//rsc string 2712
	"",//rsc string 2713
	"",//rsc string 2714
	"",//rsc string 2715
	"",//rsc string 2716
	"",//rsc string 2717
	"",//rsc string 2718
	"",//rsc string 2719
	"",//rsc string 2720
	"",//rsc string 2721
	"",//rsc string 2722
	"",//rsc string 2723
	"",//rsc string 2724
	"",//rsc string 2725
	"",//rsc string 2726
	"",//rsc string 2727
	"",//rsc string 2728
	"",//rsc string 2729
	"(UTC-04:00) Caracas",//rsc string 2730
	"",//rsc string 2731
	"",//rsc string 2732
	"",//rsc string 2733
	"",//rsc string 2734
	"",//rsc string 2735
	"",//rsc string 2736
	"",//rsc string 2737
	"",//rsc string 2738
	"",//rsc string 2739
	"",//rsc string 2740
	"",//rsc string 2741
	"",//rsc string 2742
	"",//rsc string 2743
	"",//rsc string 2744
	"",//rsc string 2745
	"",//rsc string 2746
	"",//rsc string 2747
	"",//rsc string 2748
	"",//rsc string 2749
	"(UTC+07:00) Tomsk",//rsc string 2750
	"Tomsk Daylight Time",//rsc string 2751
	"Tomsk Standard Time",//rsc string 2752
	"",//rsc string 2753
	"",//rsc string 2754
	"",//rsc string 2755
	"",//rsc string 2756
	"",//rsc string 2757
	"",//rsc string 2758
	"",//rsc string 2759
	"",//rsc string 2760
	"",//rsc string 2761
	"",//rsc string 2762
	"",//rsc string 2763
	"",//rsc string 2764
	"",//rsc string 2765
	"",//rsc string 2766
	"",//rsc string 2767
	"",//rsc string 2768
	"",//rsc string 2769
	"(UTC+06:00) Omsk",//rsc string 2770
	"Omsk Daylight Time",//rsc string 2771
	"Omsk Standard Time",//rsc string 2772
	"",//rsc string 2773
	"",//rsc string 2774
	"",//rsc string 2775
	"",//rsc string 2776
	"",//rsc string 2777
	"",//rsc string 2778
	"",//rsc string 2779
	"",//rsc string 2780
	"",//rsc string 2781
	"",//rsc string 2782
	"",//rsc string 2783
	"",//rsc string 2784
	"",//rsc string 2785
	"",//rsc string 2786
	"",//rsc string 2787
	"",//rsc string 2788
	"",//rsc string 2789
	"(UTC+07:00) Novosibirsk",//rsc string 2790
	"Novosibirsk Daylight Time",//rsc string 2791
	"Novosibirsk Standard Time",//rsc string 2792
	"",//rsc string 2793
	"",//rsc string 2794
	"",//rsc string 2795
	"",//rsc string 2796
	"",//rsc string 2797
	"",//rsc string 2798
	"",//rsc string 2799
	"",//rsc string 2800
	"",//rsc string 2801
	"",//rsc string 2802
	"",//rsc string 2803
	"",//rsc string 2804
	"",//rsc string 2805
	"",//rsc string 2806
	"",//rsc string 2807
	"",//rsc string 2808
	"",//rsc string 2809
	"(UTC+03:00) Istanbul",//rsc string 2810
	"",//rsc string 2811
	"",//rsc string 2812
	"",//rsc string 2813
	"",//rsc string 2814
	"",//rsc string 2815
	"",//rsc string 2816
	"",//rsc string 2817
	"",//rsc string 2818
	"",//rsc string 2819
	"",//rsc string 2820
	"",//rsc string 2821
	"",//rsc string 2822
	"",//rsc string 2823
	"",//rsc string 2824
	"",//rsc string 2825
	"",//rsc string 2826
	"",//rsc string 2827
	"",//rsc string 2828
	"",//rsc string 2829
	"",//rsc string 2830
	"",//rsc string 2831
	"",//rsc string 2832
	"",//rsc string 2833
	"",//rsc string 2834
	"",//rsc string 2835
	"",//rsc string 2836
	"",//rsc string 2837
	"",//rsc string 2838
	"",//rsc string 2839
	"(UTC+04:00) Saratov",//rsc string 2840
	"Saratov Daylight Time",//rsc string 2841
	"Saratov Standard Time",//rsc string 2842
	"",//rsc string 2843
	"",//rsc string 2844
	"",//rsc string 2845
	"",//rsc string 2846
	"",//rsc string 2847
	"",//rsc string 2848
	"",//rsc string 2849
	"",//rsc string 2850
	"",//rsc string 2851
	"",//rsc string 2852
	"",//rsc string 2853
	"",//rsc string 2854
	"",//rsc string 2855
	"",//rsc string 2856
	"",//rsc string 2857
	"",//rsc string 2858
	"",//rsc string 2859
	"",//rsc string 2860
	"",//rsc string 2861
	"",//rsc string 2862
	"",//rsc string 2863
	"",//rsc string 2864
	"",//rsc string 2865
	"",//rsc string 2866
	"",//rsc string 2867
	"",//rsc string 2868
	"",//rsc string 2869
	"(UTC-03:00) Punta Arenas",//rsc string 2870
	"Magallanes Daylight Time",//rsc string 2871
	"Magallanes Standard Time",//rsc string 2872
	"",//rsc string 2873
	"",//rsc string 2874
	"",//rsc string 2875
	"",//rsc string 2876
	"",//rsc string 2877
	"",//rsc string 2878
	"",//rsc string 2879
	"",//rsc string 2880
	"",//rsc string 2881
	"",//rsc string 2882
	"",//rsc string 2883
	"",//rsc string 2884
	"",//rsc string 2885
	"",//rsc string 2886
	"",//rsc string 2887
	"",//rsc string 2888
	"",//rsc string 2889
	"(UTC+02:00) Khartoum",//rsc string 2890
	"Sudan Daylight Time",//rsc string 2891
	"Sudan Standard Time",//rsc string 2892
	"",//rsc string 2893
	"",//rsc string 2894
	"",//rsc string 2895
	"",//rsc string 2896
	"",//rsc string 2897
	"",//rsc string 2898
	"",//rsc string 2899
	"",//rsc string 2900
	"",//rsc string 2901
	"",//rsc string 2902
	"",//rsc string 2903
	"",//rsc string 2904
	"",//rsc string 2905
	"",//rsc string 2906
	"",//rsc string 2907
	"",//rsc string 2908
	"",//rsc string 2909
	"(UTC-05:00) Turks and Caicos",//rsc string 2910
	"",//rsc string 2911
	"",//rsc string 2912
	"",//rsc string 2913
	"",//rsc string 2914
	"",//rsc string 2915
	"",//rsc string 2916
	"",//rsc string 2917
	"",//rsc string 2918
	"",//rsc string 2919
	"",//rsc string 2920
	"",//rsc string 2921
	"",//rsc string 2922
	"",//rsc string 2923
	"",//rsc string 2924
	"",//rsc string 2925
	"",//rsc string 2926
	"",//rsc string 2927
	"",//rsc string 2928
	"",//rsc string 2929
	"",//rsc string 2930
	"",//rsc string 2931
	"",//rsc string 2932
	"",//rsc string 2933
	"",//rsc string 2934
	"",//rsc string 2935
	"",//rsc string 2936
	"",//rsc string 2937
	"",//rsc string 2938
	"",//rsc string 2939
	"(UTC+01:00) Sao Tome",//rsc string 2940
	"Sao Tome Daylight Time",//rsc string 2941
	"Sao Tome Standard Time",//rsc string 2942
	"",//rsc string 2943
	"",//rsc string 2944
	"",//rsc string 2945
	"",//rsc string 2946
	"",//rsc string 2947
	"",//rsc string 2948
	"",//rsc string 2949
	"",//rsc string 2950
	"",//rsc string 2951
	"",//rsc string 2952
	"",//rsc string 2953
	"",//rsc string 2954
	"",//rsc string 2955
	"",//rsc string 2956
	"",//rsc string 2957
	"",//rsc string 2958
	"",//rsc string 2959
	"(UTC+09:00) Pyongyang",//rsc string 2960
	"",//rsc string 2961
	"",//rsc string 2962
	"",//rsc string 2963
	"",//rsc string 2964
	"",//rsc string 2965
	"",//rsc string 2966
	"",//rsc string 2967
	"",//rsc string 2968
	"",//rsc string 2969
	"",//rsc string 2970
	"",//rsc string 2971
	"",//rsc string 2972
	"",//rsc string 2973
	"",//rsc string 2974
	"",//rsc string 2975
	"",//rsc string 2976
	"",//rsc string 2977
	"",//rsc string 2978
	"",//rsc string 2979
	"(UTC+03:00) Moscow, St. Petersburg",//rsc string 2980
	"",//rsc string 2981
	"",//rsc string 2982
	"",//rsc string 2983
	"",//rsc string 2984
	"",//rsc string 2985
	"",//rsc string 2986
	"",//rsc string 2987
	"",//rsc string 2988
	"",//rsc string 2989
	"(UTC+04:00) Volgograd",//rsc string 2990
	"Volgograd Daylight Time",//rsc string 2991
	"Volgograd Standard Time",//rsc string 2992
	"",//rsc string 2993
	"",//rsc string 2994
	"",//rsc string 2995
	"",//rsc string 2996
	"",//rsc string 2997
	"",//rsc string 2998
	"",//rsc string 2999
	"",//rsc string 3000
	"",//rsc string 3001
	"",//rsc string 3002
	"",//rsc string 3003
	"",//rsc string 3004
	"",//rsc string 3005
	"",//rsc string 3006
	"",//rsc string 3007
	"",//rsc string 3008
	"",//rsc string 3009
	"(UTC+01:00) Casablanca",//rsc string 3010
	"",//rsc string 3011
	"",//rsc string 3012
	"",//rsc string 3013
	"",//rsc string 3014
	"",//rsc string 3015
	"",//rsc string 3016
	"",//rsc string 3017
	"",//rsc string 3018
	"",//rsc string 3019
	"",//rsc string 3020
	"",//rsc string 3021
	"",//rsc string 3022
	"",//rsc string 3023
	"",//rsc string 3024
	"",//rsc string 3025
	"",//rsc string 3026
	"",//rsc string 3027
	"",//rsc string 3028
	"",//rsc string 3029
	"(UTC+00:00) Sao Tome",//rsc string 3030
	"",//rsc string 3031
	"",//rsc string 3032
	"",//rsc string 3033
	"",//rsc string 3034
	"",//rsc string 3035
	"",//rsc string 3036
	"",//rsc string 3037
	"",//rsc string 3038
	"",//rsc string 3039
	"",//rsc string 3040
	"",//rsc string 3041
	"",//rsc string 3042
	"",//rsc string 3043
	"",//rsc string 3044
	"",//rsc string 3045
	"",//rsc string 3046
	"",//rsc string 3047
	"",//rsc string 3048
	"",//rsc string 3049
	"(UTC+05:00) Qyzylorda",//rsc string 3050
	"Qyzylorda Daylight Time",//rsc string 3051
	"Qyzylorda Standard Time",//rsc string 3052
	"",//rsc string 3053
	"",//rsc string 3054
	"",//rsc string 3055
	"",//rsc string 3056
	"",//rsc string 3057
	"",//rsc string 3058
	"",//rsc string 3059
	"",//rsc string 3060
	"",//rsc string 3061
	"",//rsc string 3062
	"",//rsc string 3063
	"",//rsc string 3064
	"",//rsc string 3065
	"",//rsc string 3066
	"",//rsc string 3067
	"",//rsc string 3068
	"",//rsc string 3069
	"",//rsc string 3070
	"",//rsc string 3071
	"",//rsc string 3072
	"",//rsc string 3073
	"",//rsc string 3074
	"",//rsc string 3075
	"",//rsc string 3076
	"",//rsc string 3077
	"",//rsc string 3078
	"",//rsc string 3079
	"(UTC-08:00) Yukon",//rsc string 3080
	"Yukon Daylight Time",//rsc string 3081
	"Yukon Standard Time",//rsc string 3082
	"",//rsc string 3083
	"",//rsc string 3084
	"",//rsc string 3085
	"",//rsc string 3086
	"",//rsc string 3087
	"",//rsc string 3088
	"",//rsc string 3089
	"(UTC-07:00) Yukon",//rsc string 3090
	"",//rsc string 3091
	"",//rsc string 3092
	"",//rsc string 3093
	"",//rsc string 3094
	"",//rsc string 3095
	"",//rsc string 3096
	"",//rsc string 3097
	"",//rsc string 3098
	"",//rsc string 3099
	"",//rsc string 3100
	"",//rsc string 3101
	"",//rsc string 3102
	"",//rsc string 3103
	"",//rsc string 3104
	"",//rsc string 3105
	"",//rsc string 3106
	"",//rsc string 3107
	"",//rsc string 3108
	"",//rsc string 3109
	"(UTC+03:00) Volgograd",//rsc string 3110
	"",//rsc string 3111
	"",//rsc string 3112
	"",//rsc string 3113
	"",//rsc string 3114
	"",//rsc string 3115
	"",//rsc string 3116
	"",//rsc string 3117
	"",//rsc string 3118
	"",//rsc string 3119
	"",//rsc string 3120
	"",//rsc string 3121
	"",//rsc string 3122
	"",//rsc string 3123
	"",//rsc string 3124
	"",//rsc string 3125
	"",//rsc string 3126
	"",//rsc string 3127
	"",//rsc string 3128
	"",//rsc string 3129
	"",//rsc string 3130
	"",//rsc string 3131
	"",//rsc string 3132
	"",//rsc string 3133
	"",//rsc string 3134
	"",//rsc string 3135
	"",//rsc string 3136
	"",//rsc string 3137
	"",//rsc string 3138
	"",//rsc string 3139
	"(UTC+02:00) Juba",//rsc string 3140
	"South Sudan Daylight Time",//rsc string 3141
	"South Sudan Standard Time",//rsc string 3142
	"",//rsc string 3143
	"",//rsc string 3144
	"",//rsc string 3145
	"",//rsc string 3146
	"",//rsc string 3147
	"",//rsc string 3148
	"",//rsc string 3149
	"",//rsc string 3150
	"",//rsc string 3151
	"",//rsc string 3152
	"",//rsc string 3153
	"",//rsc string 3154
	"",//rsc string 3155
	"",//rsc string 3156
	"",//rsc string 3157
	"",//rsc string 3158
	"",//rsc string 3159
	"",//rsc string 3160
	"",//rsc string 3161
	"",//rsc string 3162
	"",//rsc string 3163
	"",//rsc string 3164
	"",//rsc string 3165
	"",//rsc string 3166
	"",//rsc string 3167
	"",//rsc string 3168
	"",//rsc string 3169
	"",//rsc string 3170
	"",//rsc string 3171
	"",//rsc string 3172
	"",//rsc string 3173
	"",//rsc string 3174
	"",//rsc string 3175
	"",//rsc string 3176
	"",//rsc string 3177
	"",//rsc string 3178
	"",//rsc string 3179
	"",//rsc string 3180
	"",//rsc string 3181
	"",//rsc string 3182
	"",//rsc string 3183
	"",//rsc string 3184
	"",//rsc string 3185
	"",//rsc string 3186
	"",//rsc string 3187
	"",//rsc string 3188
	"",//rsc string 3189
	"",//rsc string 3190
	"",//rsc string 3191
	"",//rsc string 3192
	"",//rsc string 3193
	"",//rsc string 3194
	"",//rsc string 3195
	"",//rsc string 3196
	"",//rsc string 3197
	"",//rsc string 3198
	"",//rsc string 3199
	"",//rsc string 3200
	"",//rsc string 3201
	"",//rsc string 3202
	"",//rsc string 3203
	"",//rsc string 3204
	"",//rsc string 3205
	"",//rsc string 3206
	"",//rsc string 3207
	"",//rsc string 3208
	"",//rsc string 3209
	"",//rsc string 3210
	"",//rsc string 3211
	"",//rsc string 3212
	"",//rsc string 3213
	"",//rsc string 3214
	"",//rsc string 3215
	"",//rsc string 3216
	"",//rsc string 3217
	"",//rsc string 3218
	"",//rsc string 3219
	"",//rsc string 3220
	"",//rsc string 3221
	"",//rsc string 3222
	"",//rsc string 3223
	"",//rsc string 3224
	"",//rsc string 3225
	"",//rsc string 3226
	"",//rsc string 3227
	"",//rsc string 3228
	"",//rsc string 3229
	"(UTC-07:00) La Paz, Mazatlan",//rsc string 3230
	"",//rsc string 3231
	"",//rsc string 3232
	"",//rsc string 3233
	"",//rsc string 3234
	"",//rsc string 3235
	"",//rsc string 3236
	"",//rsc string 3237
	"",//rsc string 3238
	"",//rsc string 3239
	"",//rsc string 3240
	"",//rsc string 3241
	"",//rsc string 3242
	"",//rsc string 3243
	"",//rsc string 3244
	"",//rsc string 3245
	"",//rsc string 3246
	"",//rsc string 3247
	"",//rsc string 3248
	"",//rsc string 3249
	"",//rsc string 3250
	"",//rsc string 3251
	"",//rsc string 3252
	"",//rsc string 3253
	"",//rsc string 3254
	"",//rsc string 3255
	"",//rsc string 3256
	"",//rsc string 3257
	"",//rsc string 3258
	"",//rsc string 3259
	"",//rsc string 3260
	"",//rsc string 3261
	"",//rsc string 3262
	"",//rsc string 3263
	"",//rsc string 3264
	"",//rsc string 3265
	"",//rsc string 3266
	"",//rsc string 3267
	"",//rsc string 3268
	"",//rsc string 3269
	"",//rsc string 3270
	"",//rsc string 3271
	"",//rsc string 3272
	"",//rsc string 3273
	"",//rsc string 3274
	"",//rsc string 3275
	"",//rsc string 3276
	"",//rsc string 3277
	"",//rsc string 3278
	"",//rsc string 3279
	"(UTC-02:00) Greenland",//rsc string 3280
	"",//rsc string 3281
	"",//rsc string 3282
	"",//rsc string 3283
	"",//rsc string 3284
	"",//rsc string 3285
	"",//rsc string 3286
	"",//rsc string 3287
	"",//rsc string 3288
	"",//rsc string 3289
	"",//rsc string 3290
	"",//rsc string 3291
	"",//rsc string 3292
	"",//rsc string 3293
	"",//rsc string 3294
	"",//rsc string 3295
	"",//rsc string 3296
	"",//rsc string 3297
	"",//rsc string 3298
	"",//rsc string 3299
	"(UTC+03:00) Damascus",//rsc string 3300
	"",//rsc string 3301
	"",//rsc string 3302
	"",//rsc string 3303
	"",//rsc string 3304
	"",//rsc string 3305
	"",//rsc string 3306
	"",//rsc string 3307
	"",//rsc string 3308
	"",//rsc string 3309
	"",//rsc string 3310
	"",//rsc string 3311
	"",//rsc string 3312
	"",//rsc string 3313
	"",//rsc string 3314
	"",//rsc string 3315
	"",//rsc string 3316
	"",//rsc string 3317
	"",//rsc string 3318
	"",//rsc string 3319
	"",//rsc string 3320
	"",//rsc string 3321
	"",//rsc string 3322
	"",//rsc string 3323
	"",//rsc string 3324
	"",//rsc string 3325
	"",//rsc string 3326
	"",//rsc string 3327
	"",//rsc string 3328
	"",//rsc string 3329
	"",//rsc string 3330
	"",//rsc string 3331
	"",//rsc string 3332
	"",//rsc string 3333
	"",//rsc string 3334
	"",//rsc string 3335
	"",//rsc string 3336
	"",//rsc string 3337
	"",//rsc string 3338
	"",//rsc string 3339
	"",//rsc string 3340
	"",//rsc string 3341
	"",//rsc string 3342
	"",//rsc string 3343
	"",//rsc string 3344
	"",//rsc string 3345
	"",//rsc string 3346
	"",//rsc string 3347
	"",//rsc string 3348
	"",//rsc string 3349
	"(UTC+05:00) Astana",//rsc string 3350
	"(UTC+06:00) Bishkek",//rsc string 3351
	"",//rsc string 3352
	"",//rsc string 3353
	"",//rsc string 3354
	"",//rsc string 3355
	"",//rsc string 3356
	"",//rsc string 3357
	"",//rsc string 3358
	""//rsc string 3359

};
#endif // _WIN#2
#endif // !WIN32_TZRES_DLL_H
