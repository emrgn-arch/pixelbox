const char MAIN_page[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Retro TV Canvas</title>
    <script src="https://jscolor.com/releases/2.4.6/jscolor.js"></script>
    <style>
        :root {
            --rust: #7d4f35;
            --tan: #c9a884;
            --sage: #9bad97;
            --ebony: #0d0602;
            --olive: #5d6a55;
            --chestnut: #6c4a33;
            --charcoal: #353a2d;
            --graphite: #5e5450;
            --silver: #a4a0a2;
            --brick: #692e0a;
            --orange: #853e1d;
        }

        * {
            box-sizing: border-box;
        }

        body {
            margin: 0;
            background-color: var(--olive);
            font-family: 'Courier New', Courier, monospace;
            color: var(--silver);
            height: 100vh;
            display: flex;
            align-items: center;
            justify-content: center;
            background-image: url('data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAIAAAABICAYAAAA+hf0SAAAAAXNSR0IB2cksfwAAAAlwSFlzAAALEwAACxMBAJqcGAAAOZpJREFUeJzNfWmsZdl11tpnutOb36tXXdVDtbvd7bZjm8RDHCdSIiIgyEigSIAQCIFQIgLKbMcJIBISEEriTBCGQCIkQPAHiYhRkSKB4hBnJLFju7vdY1W55ldvvPOZNutba+197ms3iROXnT6lV+++e+85Z5+9pm8Ne+3s77zvEX9SES0rT0/tZPSeZ9bpLX/2A/Tyi2f00i/9Gj3zJ7+e5m/6Oqq9I/Ke0jShuq7o7t17hCPLMuJPqGlbSpzjz2paH/bpZDKnzVGPsiThTz0t6pbmZU1rgz7NZnPy/F3HP3xJOT9J+XXLfyT8Pv/Li4L2L+7L9ZqmIZJ3cSUv92lb/Oav8/VxDdw/TVJaW1+jXq9H4/GYXKLX18PrFXARPv/s9JTyNNVr8ZeWZSXf0o/te3wu7tO2ev+Gf6e4X6sXdSlet/p9fN231CtyOj6bEJ66rmq5tnyG6/Dn4Ujl2T3lWUo5j7Mul1RVjXyHp4IqnuNBv8+/axnjsm6obmsa8PdxxbLW+SYhC7/j8RxEw35B4+lMhg9a7e1sUpFnNJsvqKwqGeteOqVbv/TfaDotKZs3LU352fsZE7bxdHJ/QdMXPkVv++pvoONb96ltQICaJ0gfJuNJI+d5kgtjiDROLAgyXyhF9cGdEEwmSwapxBOm4YnE+L08AX+e6KTg/TBN4dx4Je/i+0miDFkzc2ACnEuEAFVVMjOleq7Xk7vrMLFIGRLnlDzJkSmM8IkRxtnYnTGMC9ew5wADM2cIgzBNZMz4LDI0jy/niS+ZcHiu1rXCBM47GSeumYjg8Pl8gaTo03I5pvmyos0hE3FRUZIVMt+4VcPzL8+fpPKsSVvJjVJ5br2vZwadMKHlviUzE9P28OSMmauU8WCucp777VGtY4EAHy0xLYk83LhydOukpo1PvErp6JfpfX/+G+gzv/ZJ4cajo2OdQn6gvMh4YBk1kBC+CSTU2cTh4do8FUmhKLc6ufId4W7+ftJJjkiEZwbkcyHR4IYiz01qvEqcCyRR4iTGGOFw8W6qSTwPzifKBLinM34A/4qo2LUhJUpIvneq2kR/2hVmw+QagZ2LzAVCOBe+r0TAF2VOamYw1ipgbM//BYEAwUUQEm8EMS3kfHyKhIkMTYKxZZmT+YrMJ/fWecKYW+M4b1oKrIjrLZYLPq+lxx+9RP1ezt9rhFmhUQs3pTTRp8uKhOQBezkPjk88Ygm+dndJye+8TM+86bM02N2nCd+kYKLiZi4D8RMhA+ZS1H4r/K+T6XHlRKRQiU4mv8YAUNWpiJVwPt6Hmkv5dUqZcGp4KJnRNoqxSFlCyvVEpmVgNUw+RQPwtTKePB8o7u06ZGPxKtFhujGJJuTKcMaTGIeqemec5uO17BI8nqCrAvsZwxpj9Vkd10y8RO6tWooSmBTVNC7Vy+I7uN5o0GPzWYi29P0eM0EmZkH0pJhG1bZ4XTNxncqFjKnxQcOF8bNpKVJmspoWJcaTsdkb09raULRs4mRUlF0asLSxrRkWfBEMjC805hNOxg3d+MRnKH34y4VwkOjEmyQbFzqblwIq3au6FCYh1QwmP/bb63s2QUElYSDg5roxKYRKE6lLVufWaKDyX7dN1B6JPIxqH2HEaPSDRNpfztQvqTZYvabZovhlkWaebG9jdVH6qPvczJngjNX3jaFA1IrVMDnFJvp5bffH95QpMA8pmJ7PWy6WTCw2AWsDmi1KMa/CiHXHyK08o85pi3mym2MsTRtMnRd8kngnTIdTMITWKWOIqZN5YxNwf9HQKDEryQTpsXQWfHJFOf3OLz9Lb/1Tj1Jz8VEeWB1J2WdpbQ38NL6VhwGnBVAHGw/gJJMXJs7sNaQGk8Nmis/1Qhi1g5kMKhW1qgQRTc2s3TRtp2rtvpgYZ5ogirNpBZikRpgtTIfZZahaUiaWiQwcxs8AEAmJT1ZMQjBrqXK2aBiPyQ9qFwRpHCnO9Ssq2gv4TXpgBBJ1266YjABgcRHMUyNzpaZxWdfC5JgPYQDY/0bni+ow4k7zqcApMy4Alg2/CDZzic6rU+w2ZEFPBTsF4eH7FIyYpww4NhnUtSbBosYarxwkBDWVIVKk3xG5gAT4RBB80yhBnAGsOBeiDRqaM/KHCioXc7ZPjD5TSLIXzdIIV7uIE/CTMQYoGUWDaZq6Pid5REETKSPEvxPFDj1Wn+VyGTUBhe/adyC10/FUiKFI2gn6dhS8Cm8MZgDVGEY8nSRVr8CYS4FxEvmQR8DPW7HqVkbEhJd1Bw7ldokTlS2gFwKAuYZg9dj294ZCsAGr/zTYefFEFAu5NJU5gabAHOL9DdYYGMHpdCH3KetSGDVNGawz5wzYrDQ1vIsBj6sS+qsZYwYZsG2fzZeUuR4zmDOCtXJCK1JRybfxkKLaWNLFTjPNiryQhxTVvkIQSGmeqsEF8U/PxvTsZ16iV65eFw4Nrk209UacztXTSYI714qGaZXvAwO44DomBvv0tdg91k4Fu5AiuYnafWdmBq8hGZBOgCG8hq125npiwoFPFIiS/B0YUgjc+uhaqhbSweIauUhsJi5XZe6WGD7Moclt8C5XvSbxivieZdWIJhwMN5jI7EbznMENBKLH9eEdYDwZ/+1Fq9SCswDu8Cx9fh9jqBoFgd4Az/HpGR0flUKf4+NT2tvdprVebdqn5esxGu/nqfnUppZwAYCylL+QpKLCoDxFMvmmPXyfb9RnkDGbVeIqGh2DsVL3jM9ZshRf++xn6dd+/TfolZdfEYZoA9R2HXb3wWZHG+yj+0bm50bnPLhtSSC/TmRi0i2mJHERH5BJdscM+hzx+87F9/Fbzk3NzFASGW5VQ6lyUBXXZ0bd2lyjQU9VbGLzoBi2NaZ10bxBm0ZsSaopBKHzM25u79M73/4M4yrGINAgDGgxxt3tDWFAuK45C14qXlLLQqLzNefPRqN+BKGqsfg29ZKGfkIJ/x6UN2nxmY/TgWMNNshomA8oe2wtocujHqsccICqHUjTqNfQdp8f9N6LNFycUq/tCJZBA8Au8ySN+Fo1n3d7/a3MiY52/Bm53gUa2xMuFgu6desW3b1zR07f2hwp+g9Q2tM5hggEayOC8zHw4r3r7GxQ8BYUoihpNgE2CdGktb47y7wHu7rhq1XQGK6k3/UrjBrVuGEAgNcBo/e97U1RtxqAcQaEG/kR0AmGSjNhPAS5ksCA5MX2QwNM53MaDj9Lj17apdH6HlXtklH7gL2JHo0nM7P3rotNmHvpV5itMTDtvWKn9fIW7dz/lGAxjAX38oYVWH9QdnAypbINBkwJoGqJrRkjx96tY1Gr8EeDlG0yYwyYM5eNul0j5s72rW+S2EB2do3yrU2BnQJsyiXb2zOajMdKYH5weB2C9g3UIdBERKaSLbC0ouoVXQd80sZgjFIjMYK3AuY6DUJdnEE+jzyjBAmugGkFVfHUaSKLaTTGEKuSH9Q4JnjBqhkYieCZsK3fXB/SOrtaGMBsfEoVo/lWPIbE5tHT1lafBqN1keQFY6Kj0wmd8ACHwz6r60Oa83mjjT1+tFQieDhOjk8oeqUuaMMwJn0WWMpA/PBTV1P69Kev061pw0Kv8RNEZb252NndRUt3Zxp+LKAaEcGCrWHTAAbImREQ9HvTE7t0/dYZ3T+a0TP7Ba0zE0yWtXgHT2/ofOLm5ekB9ZY82HqTb8I8xiqr4odUAjkBUtAe3un3of5gMyUoATuapKvyHQnaGkpXN0idoCiKr9EY4QIBdSt+iF/t1HniLARGCnIzndTEiNwG7eQs+JQkFoHUD2HmarG5Cuj2mPhPP/EIPXTpIXmum1dfoft371FZApDyfGZwCVvaYpf70uV96g2GdIe148Ht23R6yip6NJBxIoQscRGvHgDC7nWtLuRwMBAv0AUmkIhiIi6wPmpiDGEhdY+AnSOEE77soRGD45rGi5pKMC8zbIbv9nNW+UzsAf/0JSiUCLf0mLPzXIHShbWUjocZ3bzX0rwCERd8U2UQ+KKQPfw92L9C9dE95qY+T05KDRO3YSbw1EkjCFkxUl0wUkcMvhEXsnuooJrDwwSfW30436F3C2iEmLggFdEQLUUvjxS8eQsGeTMpnTdBFEGoxTvAhGlqmCBx5qsnhlEs7iAktWsY2AS43Fpfp929XSHYPSZsIgBRz8G8qifV0qNXHmOiwNuq6LnnX7IgGlmIuqHJbCmzAJcc8xTNr9HjkDV3YPkt1jgyXpZieALKGKxRABCcuqF9pueyVDANeuNzaLdM0DIFSVD0mJCPAZpMLtDSneuHrIYqBioMONjFmcKOIGSbIeSqwBHXmRZ7tH78Im1usLtSLqitlqIFnLmOCMaAqyfTGdu1qQR1BMtbLoAsXBwmnQSoGdrPjBhOQZoCtsRQuwLERrSKETi4rMGHDyCy9eb3t+ZmsSkLGMHAZmpuIAgYmCF1qYTB+6wSxV00EsiMWSBqUZU0mc/Y3S3l+YBPRPWnGpmTe8HfZ8afsTu8YNEczxeiLaNpE5c0ioxgB1NT4ulkGQNABnbQUI0xMwRZYhjG2BjzoJdTqhZE53YF9QSNKAxQy4UQCtZQKCQZPnrRArHzRDTwy9kUZETBnclM6vp8IwRrJJEHH7XYpHGxS/7qx6ndflSyXGqXKIZga37omUW9AAjzXrFk/PAKf/Zb7Gb+qm/qG3zOcZIlk7QoZlnem6VZIdLHQBA8NGG1xkPzGJpjYjE9WMach3OS+NTn/Fw5nzDg7w94mEc4i3/DOG+yBF7KfPtmZoDHmRmHTCTMA3+XRjzAHR7oBQRj+XWPz1lDII3VPbv/JaV1Lf7wANJ17tCQ9uHxMavXmk7HU7p3cCjoe8iESAoLcDETIb7x3LPPiwo+OznVRFsa8gXqHiI5hwPMU1VptP8Fwtzei7sZEH8Sg2BtzC2AYZH98whFe40zOB+RbwxcZYKs+QlL4xJ+PHEfoJ6a1AXArGFaCvaQaG9N/WlIJx7IMAUt+aGqYpuR65yWaxepOb2qdjuALiKJHkICWXUycYtrfKsPV2X50X6/P3t4d63Z3d2g//0rz9kJZ/TFPL7+a9/GTNMmVdW46WzhZvzDdtLNFrXz2aif5v193zZb08mYJ7N677BX/IW6V7zLF7RGAYtaYAfq9+PPvsKgmiV8wdhHgjUwqbkQDA8UMFD13C1CpHjJAjJA/GAzBTHkOwDg8CpSPgcBsfbugSZ7nEb4xLMwkOItG4r3xQNgbduQmsg06fHnmkVszbysekT4nQnowAtIvqgx5p5c7d0SESrGZ7lX21o3pl4QtcLADE3XEjVsJfuEATtWgUV/jVx7Svd9yGSFOAOF+DrPZ/vbdT391/zWx3Z2d2dFr5+ezKn53Uj8L+x47Okvc9df+PTvea3/9dFnYRjb1/90PH/kypsWPNqDcj6ds7/fMDh7C0/uE/zhmgqshKEEVN0/OZG0rTC3C2EtHFW8Ygxp04qZyoUI6mqbawn32VWscpOlmKM5gzdo6uEIDAfpZ4JLdAaYKLWQu5dAkDpImrJHoMhbNLGJ4WxzraEB9LeTi+cML0t+Y1Kqy+BJQRbmx7WKJCXyxW+N2J4hll9atg42LmPgR4nmuxcDxgL+jAqLkwfbFMKQrQ6m4sGd5mnW9Hr5usvy2dWXX3ogxMfx+xH/8zluXHt1/vS73n9huyonVC9O2P7fZSBWdi5mICoLgCS3Vs/WpFYmGCCT74nnwKZCo98WX5DIZBM9HLxbSZ2BInzXqhtKwlhJjAVoyl2DeABRmUVDvakm8WYguIJNWnH/BLl49ftxWmaehIBAcA9sfpEoV0uYAuaAFCiKpDsFSDlcRP5GjoSQhFCRfGgloOGrSnL7UwZCFSWqfqhzw/QA2vAwpFnDOvHatRunXyixvljHC7/9q9efeMvTectwJkvSksFWqAmykK6zeIGZV6dJJUQId7a2aG9nh7Y21yXGf3R8Sp+9dUdCvSC6KoGGhc9bHEIZY8DCP3BLiQVMGYQzHpI6i0Gqd9mUqB/PIjMT8gYhl7G7vS50cuYNgczr/ZSeWuszPnDGYK3kemDms+B6IEeNCFYaPCqx0wlV5n0tUDlUazhYw/xqR0K4dfPgk3LjPrjt9Jj69ZHcqDeuMEp70HMcAIbI5Re4q/mS0PIPfaz1mraCkm4lketj8MkOZ5HP1uIQMIX7F/bo4UuXJGeCBFLRL2h/f1e0APIvVTmLIeHVmUlL9h4+/Ut068XnZM68hakhZMdO/z5hlZ0wIOzx60PR4Go6rrz3/VQ7oHWT8sWUdrf64m1ILYbEPqA+9CuI+2gQwXUPsQSXtPBfWfJbdUiECZCw8JZ3FnWGpI/ebPrSJ+SaAvaW/Pe9q6Ku6nTI3FbKg0V9HNEuy4Tzpsr+P2b4DXJsbKzR+Gze1BUK/ZRdvWXpwhFeARQikbO7sy0JraPjE5rNZnT5oT0RNmiDrc0NmrOd1xR5MI2mV07uUH9Q0jLRed/aG9HtO2fUlqWY3Yq//Inbc4nOXhzlhET9cFDQ04/vk7vxHGuLnIaba7S9yVK/P6Jk78tpOltKwK1aVvTqtTs0ZJwHY5E9uZXTk4nW9wUujFGyxKSd1Au4PEpojvw3f3e8FKxJJYMMJC6AJiXggXKmtJWiRUjB8bJj8WACgrvjJBfDCiAN8bg37sH+v09SIF7XGvbqMgZO1b5hYjkyK+aYTCfsEp6xK1iIa4jYwBYzExjq3uGRuIzOdXkKDShh3r1o5F4/Zxu50GKXVlIKwkQPrUk9Fm30NEyPFOHN67cFDCKQNC7bmFfB/+J9iKLVgTuLp2RIMyKalwk1KBI9hENxG2EGlnQEXzZJQ8WplX1JZQ+7PFmO7GBfmGB6tqDt9b5WEpdhCJ2S66JwLPsJP2ieuCfefMG98tLBAwOAD/poGAV7JyUSCH2loUzUXOouf2AADEwOZYHYAMwpEkY37x3SeDynXtGzdHE4r8t5gLNqC5ELWOPzMYUOAaRQ9sfHw8NMsALA+3TphWEusKYglnTPAH1n4EVQa3P5KlQcNeqxQYPL+2yWshtTRqXMPYgS4mJrfLJExQBsmMiVfJliuVHKBMslSseqiRHJB778Ybp5d0Ll2ZLqgznbyoRQY+D5gvfZFJTZekzz0rkJA4cDADuXSb4h/5IR8w9zoNCEXcDUlXXB2jA5VwFEROQ7YgoWaNRlkpw+a0gI2mSiFbsI5owny1iFFJJXZBE91FzM4PYhwNYi35LQ6ayStH1tpVzimSGAxxq5hFZG6RlP6ISBN5LziPFDzcNzOOJzz5hJGsv3XBwwQM2dAP7sGjOAt+IMEHaHOeuZvYECmdTUEVyZVBNFcGmKVNVOygNy/KAXd4Z0/faZcpcAEib8AsEQZth1vyL8VrVr4EnjGs4hRLqxMfqSEvQPeiAJM8sXDIorgQBdxq0LsOJQJmBpW5YS7t1mLwDMfe3GbWaGQnIFqLE4OZuIhlhNQVudFZK0tGDslW2t02BtQBnb/ruTUqq3odUbrzF9CVXnWFfAJmFvgxaLpeRuBgbSa60UpQvDgvaGFCOHsBitZUizQarZL1HpUP1s0xezpYAb3AzmYR2lSoUa8SVz0oTU14SNGvU0Vj5gW9V4K4OGywiT5VyU9jhNXoMSWvjpIFMJS0iC7Ncb+ZD4v0M0xJcC/1Y1QFRxHRMggYNQ8Gg4oD6qcPg3IoIQpkMGhfcPTyQnkIQTbJ5UQ7a0/eg+be9vsqdQ041PvUxrffbYi0KYJoTUMdk76z3aYqGDED7/wm0apki0+WjCF8wEg1QL/2WGjT5Vq7mBDO4DlG9qdQBQ9Ts91AKoWwgG0IogTa8WiBI6RaehHm/O6v50jlUrGZ1AzaVaK+XyHqsnf94ExJy+gE1E8eV9VA69oQ9Gauy342AFt4L9V2gfEixic5EXODoWX//w6ERAIT5H0QfAHzwAUfmBmBQVAW1sj1jgPM0YNL76yauCH97+3icFg2WDnDVrSWcnM9rc26GKXe4lA+2b1+/T8Yy9BPYGUom8K3M2ZnMjwJf/df5BQ80F4J/roFpQEcg6wVAj2gcQgTp3yZIx0EutajXvs7uYFnQBFTH9HhVDJvq8ojkP8N7tYzo4Lm0xhAsTaU9rRaSOcZXTnMIb+UCtAgjPpG8ajbAYM1MMdHWZPBxOiH90fCxBH1lI0zYKDIEPJH8fgKC5SV7pMDmb0UHdSF3mYl7SE08/TOuXdiTWDzwxnRxJWvjg1gGNYMubRNxECNuyaqlAgCXR0rNEgngAijV7DGEFhY4ZWjpTl0BGL5KNYM8pn/bIHtsfEFNsekNbo56cvMH+K8GHRFAaRYWpkxxAmw/4gUtKmordnII2hnyNp/bIvXxGv3LvJbl+V2CpoUxk8Io080VW+F22jW/ko9A1eVHxnzuMGeB/e56D1eVm4UV47sRqDiTAYxoAuCq17B9qK1KmzsOPPUSf/M3neb6HdHG3T7usFV5kbYCIIYBkr5fRBVb/iPj98seuSRIOEcGKAeS81hpDcBO09Dab8HvTkvpZjzX9CuMBLEpdPohs6hzu4CduT+lTd2Y0ZFWwxwN4+MKG5O8R+KlunFkWqpVybSmbYk46YC/gyYe3aX1zFCek8syZVWFLu7rZErDjxFfO+WEcFjRug7HewIfU7iNs5X1cxBXjAOZbSxq9rC3mEULmqSRl+lgUO19IMAbXcm2AfJoXcSt2YDKZ03Mf+6TcJU/5PNYI/tVbtL89pIoluWAzgKprmNLlvGWc0aMha194APeOJ+xBaEGMM/8S5gDAHaGb1HWFJ3OEgt91cShVvks+g70FWX36wv0pYdHoKT/E0XJKJ+Mlc1e31AvSgJrAHJk/ZhKonHTCNu9gQnfunpKWMyRS/Dhd24wTJL/arsiT1X4GNyBjwFH7N3YsWDJprZnTVXfvNS4u3GZYMxAfRL+0v0eXL+1LnWDJFLh245b8LObLaKcdhZJ3zQOgEjjpD8gvaykaefb5m4raGyUs8gIwmz0GliPWzGvsQXkm8GgxlzUID+0Xsi4BQos1irXFJO4txW8Uk5BZeXv26M6I+qw6PJIOSy073l3vS8EnKmsAFFCcMOqnEuTpsbQWPa1Bhx1qE3gGrZREw/7A9djeGtDeBXYl2e5dnTFWuH+TIvwIk+akkiPRIFMiS5neyIdmL+XlOQuwUp8pnzey6NSJV/TopUt05ZFLgrxLFH0w9Z547LIUkb708nVZIKOaxHc8xRe5xB7An3jXJWprDdFn5iEh91/LYhnS1VgVu9qsVQ7vHmrxKdPg4QskMf/7rJFHPAZUKp8yOExHhZgXZHm38lbrAKAB7p6UfONKOFdXU7Vx2RIGBAaY8osjq8vwsnZPXTz928UliaFE++rRhJJr8C0ZsfbXmUGa1frNOIeyhDp1PmOE/bkVNm+so2JfPCx306Oz81YsvhLOZQYYDGl/f4cK2GVk7NgMTCcqkW++8gh7Aie0PDiKSbVYMsn/XnnpDv38S69qJNZp9VUQj+B+qiC1ao6t4kqij7WWopetZnebUPFtwwUGueu0QginZ9NFbV9w8cJhwYNU7lKoIXPyA0XdKPNQCIo31C2UWF1Fk2TMreuFLv1SP9IyjWQuEDwAqfL03Vq9L+z4yZ/+XrnFd33bj3wOVvtCjlAc68J6sRVF4Fe0gKSHEdns5VLsCnPw5JXLtL+7zbZ9Sp9hyYdLuLezRcdHp4oZDAwGLTJnL+pkPqXctVJ1lYd5g3i2RpdW4wVCh3ZlKbvrzJKsvfZa8BPoU3tV/UgFVzAB95bawCBbcQMDAwT3prVHrqW4gDqJX52AADjs3SATja2pC80d9ARzmIUDgIe8O2N79SCOJM2kSPen/+Xf9d/2t/7xA0sxpuyEA7Aksirex/hN+xo2C08Pyz5mMAfQdfnirqRhANbg08NrQmRRC0tVYyTU9U8oeZ4nKA0X6dfIHVm0Vsq7qItCtlEbdEEkrbdqtW6TOnZVre91US7p2szsd45mktzJXVcPHx5B3JaVyB5wAd7NV5dUhe8b8lXrIbVElFRYnFjLjQLYCflvIRZTK2EQmLIdyB5QJJBhhddhPNj0Mqp4SOiEZDtaT6iorFbvdtoPHlKjtYKwx4dYILLU1G/rpVBkNp9rDZ+ZW8sGyTyesVa4dbqIi1CitTGtHKwQfjWREUiqgHfXB7TLgHOTPQXkAsAEyDhOGHQejRkvnM3pDOCy1BRAFkqro1vjQjxauRIqRgJBjS627KVJtEOh+NBZMEnEwoxVqJkPxYhxyMHE6INJiwQogkH/wWCAb/2Wf+h/5md/oD1fYvGFH9qryEeJe92r2/tQyfPlUj0mBmF37x/TrTvsnzPo295cl0Wk9w6O5ZpB43bXcxalcysNIOLlzV0M8xdWPRM9tb9BfX6r5HucHhzSQaPVRiBHT7y2hDYZj1zZH1DK4zuY1fQC4z8JP0S1/5oDNgLFjo3XBQppUENhCJa+DIUklqSKn2ctdQUTzpuNC+dLPwvPEuJ5Irys5+fj2z/8V9w//dH/8AXZ72/55h98oPYfR81+1Xy+KMuqmfMc1GFxSFfcqYE0/AM4m0zndJeJ3M8LadyUpT3JxSPkffvGHVkqH1rfhPlqo602KXeq8oU+UfJ9gFMKEvnnsZ018uwN3GfJnrCqPquVZgB5jYA9rTlAJnDAJ65nWu/x+O6QbMWBui4BLoa8dGUqH1KfxPeteRLpmrQ2DJBU2pNQGEGmnl4zkSsOj/5tuW9M2Hcw8d+oIeGG7dhstmBA3yz4ieug6aIdtorbIMnoD3Tj1gGdjad06cIO1j6I3398OpFEUFmWFgkMd/ChWjoWzESaBDtA4beP0r1epJSxtkH0b8ljOCzbmKEMC2OdmYiS53rC5x+WnraYKSt2FYUB6rbTABLBk6XdequC1ZUsHlGlpDd3wf514GWVqOpuKHhJX4v8Vx7Fryy2hRn6J68j+R/5qe9z3/OdP3zu/Z/9uR9y3/xN3//Apfz3Ov77//hVf+Wxiy0j1prd11aK2KIx9rK4A+sAtGYyNW3Y0CkTfDyeamcOWlm8KXEQk/6WYjAoEth19YUhxRxC6GEOQdQpa5QF0wip/9N5G7GbN76xFf+yzjDGL/nXKUxFSVoWDpUVbFtorqQ3SrQfj5yrEeTMPIaQPQwUDEfMbnkyz8LHDlnyl6WI9R48kcgHFIXbeJ1cwD/7mR9w3/otn6vOv9TEj4fQpVvhEmyy9BYAYu8PiA2Erq5m1Y91f1GqQ92lBURCgwyJ/cuq4UzLysX269Jt8dUt7hK9KN8hBm8aGCF6RPsWdbMinHoEYI5rxOV/K3o5k7SEIwMT55F6Yn69qHM7IQlVwRT60zgK15D3WvUvI2e3HU6Wa0X1JJEttLVBmtWX9eemg1+P+A/6+KZv+0b3cz/985/XfcKXXAC29gM7vL0+YmKOqUn64jmhygmVOmGdYlXXUfrh/hXW6gXzIBgB0cJKcVDd6nK91lK0Yc5ohfVaC7o583fmWN0FZnLna6/Dsgy8J6X8JqCNETnb6qW6sNCde0Q92bgJngBsS1B5TViZbQpHfMtWw8bBVUEqEt0tqW1WRx6lX3zSup43zHXLZeknDygO8Ac9Pl/iy8HilRZF5ssymrSgWVEGt7GzTmuZrgFszU43EmHVrihYC4m/EZ4VE9IqWGvADOg95CsRrro1/OVUG7hVsoRmmaK1NSKhImiAMphaR7FBl5aCYw1AEsccViVlk8rHIlD5IZXw3CS98fFZNYLUKgcHd0TUT9taDCGJZgZlU1J63vqVIEWHE3C0TVNh7QEiZk1Vfl40+PDf+xtuxKoWlTYf+uCPfUlNAXBKXvTS0M8g/CNj+B7r8wF6+jjrnegUurdeO4f4nkZFg9nU4syGFggaWYVOa+51TStJM/vf2fJ4HCJk1KEuLdqxvxKt3JZx+U4LSIcBrN1g2/zoekEPjzLKWAGYPVfiy5EoYsT6F3DNuZ6LZruQdw7fTyNyt8xWwBqJWcwgLRZaDG6nFFh4YR2H5NLvd/z4T34ICURUksvxoz/xQT+ZzbAK1mdp6ofMGEVeIDFG3/XtP/rAmUMVIitma1DchkWXpGXXc5ixprbKKl0+n1rrO9WmZgLi+2pikY6PfcZksltzn51JrHVfs2CRQqrOnOJ4aNijtz5+gR7Z7NN67ggtvzySRUssQ28E6Pf4JhsFGLXBcmdNNIlPGJ9QF4cu+dt5ou/XEb8FPqTY1i1Er4LjpxpKxF/MQdfSxZBv8JlJtQFcK7b/DitzsVz89yeAeBzeIm7RcbGPfbjud337Rx4I8T/4ob/sfvzH/mNneTE/i3nToahOQpEiX+OJ3+hl2kPJnrPreRTcZ+trLKezkNWadU1Cmzq7bKcx5WwFk6HRpT6ovHh0e02W4u2zND+xWUjJXr9IJMMLTNdgHQvusaikfgOtfiXph3Y8AKsS7SPNBNbqacgDYDHhOjJZvjUptqdutXrYm9YIKJcsIhWwAR5B2pw4sjZvKypTbASaGNW+Yvi6LCtfGwj8q3/zz7l//6/+y+sS8Lu/8yPnbcgX+Vgl/jPveNyV49IFXHxuEE4bMqCjCuokihAtlQ/DkuyubRyZiQjzGSS6EyrSXse+ayUXAkNdWohEygr2NI5Z0j9zb0Kfun0mawcHPA50esmlOWRBo0FO6/2c1vopjVBr4LWYBzUCGWoEgAPqdhXIeebmRKNIQRORcSRKwyk0iQgxAZ2F4KCEpkXBMIRkkjCHcYlkprBWDV4AquyM2x+6sPuAyfhgjrqq1NRmaS4LKeXowDLAHBputkjirCwRdpaeC42vg+cUcJG4b2AOa0ED7mI60V4/k2tKFxCvazPqwP6WHsalS8MJSP/O2OogEuiWWgXssDTXLQTPoaajxycgcLTGgr3OmgpdYbNt9PqrUUgINOqlXLi2m4R4fkDtnawro2iLdOqACYVy5JXgkIUkrdzFoj9h/lwmkyl5ZnWBPvKP/s3nJeE/+EN/2/3A9/8L/+P/5EMOlTLf890/8UXVDKkXhZq1TV2gLFbf7W4JdVpkLP2Z+kZ4wtRa22AtkXbqbgTd4wgrijXXbwjelIAsAIJWMUCO3wj0oISr9trpA2liMAa8M2EoIukVKB1IKTTyVlqV/L3JUkvQ784qu7aOOVswxyJGLL0j2adQabWeM55WYvdmt71eOYkPvsIYtmol6knnYx/9cHSbK8A0uLzh/9iTcGXzBysJA/Hx+4Pf8aXxBKwiKNHYjfpioTOZIGwm7LytZFFtZg2fXCiucdpLOQA6Mo1RS28iZASD96Tqto2GLnRo6QQxhHVbez0tG0n2tEYHqQ9InHpr3lYCM0tlLtCGzEsjkbvspGoFhdr7MY4slwvvG4Jt44edTWo7WEJJlG1nD7Ma1w92pEvTosAy5Lbdl4SMf/gDbXCoDS62i1gnROhCR3VplBHayZpoNAb8Elvti3Jv1RBKMJcEofDi2K8C5RhBlZsY6DTBxEco9Jw1anaC4UnazkXU4WVUGu7qaKVHVmlVke48Ef6FZASp/Q6dCzrMa5Cuux7ZiCnAlFAl419D2ND02GvwSJya5bLx5aKiN/LBoAl6r2AtNyTR3C6WueFHFtV6Zyt7qQu7iy/uJGAjBGnUeOq8GBiGl4R+7i6cqIy1OnWrlQfdwpyELu9u0tF4RtPlQgM/CCTZItKQTk6dtaklZ6UsnfnOWlPrkWOCtnGdS6f9AQIH4JUVKZKZCeouGuoJQ0eq4P7FB/FdNQtywFCnkIgQ9HijHrDkPOI9dmkfZ0bYjFrQyBKaRaa2cFb9dZWAICOhzwLsfmOJdEQQF6YUY0QWcRYyzERBk6o5LU2K5TpMh6vHM9mLCe3MchtpyMjixmpqYHgsMNV2wT7JWQQGyEL40m7p4wPG0csRvAS/wuLObFvEg840gV899zxHC/M3Hom1ghkiPTrSDjHf/b1/zVlfPifdt7Pc/4O//8//SLnj/V/1NnfjxkHBjPoQP9UVl7oN1ASFxZY4tNNqQgXSs2j5RtbQMgIy29zKWZ4e5zZaLgfUl8y79QRC6FoFx7IDasudov3MaRh4vKwFP4DAQ+zz4BTwBSMb6UhhJxRv9l/HAHc+CxU7jVG+az7sY/g3lMKHWH+IfsXMnmmIlGy1SzQTdvMwUQFQGhzg+2/yd7f5a8NZWZ3wW81P/Mi/Pcc2OH74I9/pvu97fuqPjAnGZ9OEmXKLGfZxnrjL/BhSvhRwgLjE6AnEHsB6r7B+x95gT8i+eampjP2IeRIX3qJxaXCNjQFARNvhJDetss5chPUX19kd3WMm2+0ldG1OdMQc8aZRShuJCuH9pXZjO0VqmhSQwtGqzq276NL4WUCUYYcMolUw6GgVwStrrAA738UukgDyQlzAqR1rrR0ZDjyYLgDxAfVeYK55G9/314s8P3r3e56a/d/fevFzCB2If/lr/wz0GxytQlwMnWX1NxLX8Kvyxi/+5wdaDPi+9z6TLOblei8vniZfv7uqmksUgVAHgPCYiKCOxc0q9bkt7uEMoDWNhYJJu6oWLpU1+21MuOivATPQVj8Tda/rMj2dVapDd4c9VvVabLtbJDRlEPdQQULkObrAp5pLGOXaI3iJXsxmxsOGH5pUSAV7ZB2k6/CcwJDgt+u4YnZL/1Zity7kDzqhjUAxAMdg84NWaTvEzPY0ydLs63q94tXRYDTPs8GrX/e175nxJAvbYMXSaNCngxnScAk9urf0z9+eoYZg4ZLQeVOvt1ak/on9nvd//QMydCxwqdG/3gy1x2x4aXPvsaMWo3rXho0oWolGwk93CPjIFjVSruGK2azaY/X99uFw8IEi9++fzpebtWUD1cOzngc2L50rTBYCD3jQSQd1sb0YkbV1x73qJtBf/0f4XBZx8IVGqbZyEVsOJuOZQacPBH1mfCJ8/5cnlYVZbP6NHGjmgewkzpnVXUTf+wDuJURxHts7+ydaCSrKgIguiwqBnBWSB87xCj7OjYCsfr0NgFCFEyFiNE2ARhgM+k+vrY0+7LL+X5zOm/9UlcuP8vMdVt6Vbumb4/mCmEucZ0/nhZuVJS3RL1Z2XdIFRgxxy2WbvHhTKnLEutRoJCtbpUkZdzDZjicc4XdXN0nG76bAH6qp0qxtm8K3zEm+XeNBP8T3eCJpm3cw+nvnaFBsbw77SZHPZbUvOnJ2DrPGAUSlt7W11wtRv+ApaH9j6dnrdWKQCYR0o27A68L9bueUJASUdL5hr9Esd4inyTVWABd+zEwwRNcRe8BqNadASrMZc04ugaqUtod9WSy6M8hol7VM1nEySfcpjdqzauH5XSRa2gTbNuTBnlUhpu9klWkkcyR6Bxw1fq0qr43f0XvJsjLbVq7IC1ek6TZTZptV0ldMoZoo0cUmuA4yV4itJyERYpMDyiedDU7MFQsuqD+nfVSjhQ6ZIFbYyiVqNfsMq21dq4TUDzVnv4y7K2pjDClzWPGBZbk1In2ts8UZPkq/LNNG+VcTKNOtl6hk+V26on3DOqPu8Kua1lH05xGOlCCe1x4P8tyti1VZknK2U/JU35div1Qbgo7RLr5T3lgI2hDa+oUVPEE7MMNJbDpIP7gmdT5uyKjnt7Q2HLFqyWQt+inWwWNtSmMTvvJEIVQsA0TPvBkaIpbWuQqqXUGUrhu0RanUZR1lfCu2NXgYQNhhI7FAgNjJw3cbL4X6/NWC5VhiHZS5VPVkkqlbsllAWnU6m+u8WCUOwFkdsqSOrNW8bQMX7kfULfwIYuJsXyIDz7IdH3V7Gqz2YVRmVrdRzvP6eeIVAkGjVPy6H5Lzhq61FO/8whWk+G+czemzp/OI7TJtREgCGIZYnOE0QRFIBdUzsOwf8uz4QZ1abcYEa9LhmpwyN10/nAkELWT9ADFUxhNlNI4BE1tX2IkdBYQR9u1pBKCoeg3nGEmjtDrzYV3axR4jiHGd9HQg1hKxPpijzux1gLf7W/rryjequOevMKvZb9lPIMtihxTBQ7DNdSim9R0DBuaw7KlLrCObjbEJHphRL0s0F3NUkzST9kLkVnIBuc1rbu3pG9J2ctU5FavCVber93f02GZfNpb6zbvj2NVUGOCo6VQr/petniKQT+Shx6BjowiybFX9o75sZ1DQTFwPbWBU9PoGMtjFgZpLtIuId7VMmjSYytIoy92iOooaIfgaBvAtmui75wsBJqeYIoCaTl+93uEicFW+8939/OqZnZ4JqdsglYll4GL0L/KvSjp2TllO57L8WrRMG/VVbK+b2rJxJ8UglhACw+U5du0wUSC6v6jpLqti9BRKjC7ah0E30gYd0PY1tfPXci0pk4qlRPs2I0cwZG5Z6xdSG5B7tOivaINBITb8gJMIRsuGpBWlQ3SXCsuQbUIx4CxJzVdNxY4M2fXYXhvRtcOx5Jsf3d+k4Wggq2BHfDPsYbcx6tNw2BMO/fjV+/Q/f/slSZXm1lYmhJG7nHmXQVO3MmQTOwC1miuPZRExFX1eop0h4s7uhB1BKD5fbPbsguJY+a4xQldz1XU3CeMJmAQHlAqqW48XpazMCZtV+RjJo5i+leuHLV+c4oMRz+fecE1GAOO3PUjp4d0BI30FN6ghHPVy6TKWpOe3rkHdxo2DE6lHQGHtpEKHtoqJXJOfoHfjUsrUpEgFwJPpWSZaSSyh4K+52Ndl2omptqCqnO3MYbHtV9kRRbwavQEO2I4gCQGOvHb3hAl9Rn/s8jpVU08nxwmdQuWhIqU3oMXSyZYmEtlaIcDrSW1nIz9XgqOtPxeXIOqikuffk/ejenDxmkEl0vkzYgDrXLwy8tj564sb1ejqs8J2EMGGT2BubNIQO6GKN9BGMyTMsvI03rQAOohh0SgIO+L5feeldVpjLfscq2sUcFxYK0Tb8q1k+TeKOVDpg4KOOfv9+XqPfvfOiVRjz5o27vzG/rJ4ADPsqE6GWQA8vdIajm6GUiKJCVujhsT2zUtT245F9yKh3zis6MZ4JpN3Z6aAbcjq5MlNln4e7LO3Tumr336F3sKDR10cFknMmRNRCQv7g5h3GYFXmIAubNlF1boki4Iq29gxJDMM4se4wmtJuYL8YxPG6Kvae/Yv9NDvIpWdO+zpPIBcXY0rOIs0yAOgiNavI9aCu1trWvodNJI3T4h8ZIpGQYaGhW0jLey9jMdiV1MaPX30hXs0ny9pb2NIV0ZDOqyZkCxIG0lBF3b6UnYG7Xv17ikN2af99NUX6PELG/T0FptkBmQnrImOGFgfLxop9lnn61+wApNjZoib4zkzhW5ClSF0GAII3rIBkPycOWvQY7WR5vSpO6d0b15LE+kJOl049XPHbGdePJ6rXeOHufEbL9P3fuNXst3pUz4ievbFA8p7Q3rHZkYvsqa4N15Y2Fldl9BnQNLK1o3UmclJFTFFmymMaT7yCg91+CUY9MgM3tK3vlP50ewEAmtFc7DlEWdQiJdbLR6FpV8rbiVR7OCNLp31craiKXQBTWOgE0GIsM8vFmYiZwACpkkuz4ud2WFuH1m/TPtsQhdnE3qV52tr1JfuoC/z6+v3z3QhCV99c1iIF/C2yzv8vSNZE3BvuqTHd9cYj83oyYu79F7WGmNmgjP+uXc2kzZ+Q/iN7KE9dnEkq5fPmDmyX7h2phsbJbZlXKqbMJ2igoQHfoFt+e4gpxFL+9h2nXImUbJ+0Gv6ETVoT2yPlIC2zexXsUbA9inoHXj9gNFn1dApA6XxvJKGxkGSwlatsmTZ1HWeuGCsrcDUxRTmqv3u4Ksjt/KeiWDU5WEVU0DpKwgwXsrF63URtQBMO4Rg33E+mkrZiTQJO4/qFYKDEHxy6f/rZSUOrbM9z6D2sZlz2kofYDSNwlbxLx+P6c7RWOoP4ABNFo7us8SCLlD5aD2Ty47glTDwXTbHF1nzoGn0S6wRrp8t6GDe0B9/5pIMHgBwf60nntkpg0toG+QkttFvED1J37U/EvuPejGsL19bH9LHb59SPlnSl+0MaJ0Z4Doj0kO+MFS4bIbc6ASNENEz4IjWJzeOzujf/eLHWZX16CufekRalz51ZY82Rz16irn1Pg/2+r0z2RKtiQ5qWBBJ52xnuYLuW/u8ac/b89XDnXsVKXfusxVM1qUs6DUXe51rU2Ca8Br4iHy0q2EnsyYAVzq/DAvMh8abANKo1rl1ht4Ap7oZtQ0GS8PgpgmA7vWEoTYYV1xgeuzyz3yh/YTQnh+uICqMfveV2/TOxy7QS/cndON0KkB+h8/HvT752fv0nkd3bEMJ7EGYSUr4xaMFbbI5OGJmEA3w+CiTQa5vbwr3PH/9kC6xrnj341tUDEf0iy/eEc6RzYqYA5Fu7GWZ+cuoNauUePibbc5bnmCvoCjoFTYbv/7iDVr/5DX6S1//TtpmRrrIYOXeWl8e+ni2oLD1szdkn7hzMioTI10yEgV/6IVXry7O9+eVfifVKy7fKhVfAxg6IPoa0xG+6ldAqZmqQFxgI63V0631UGihLXPC8jkXXUecLAmZRsvtR+jO3oNLXMgeDNCAD20NhYBw82C/ZQOp5YIYR/N3KkH4mO+TyYSmrJ2xS0vJN73D3pgvlyyMGW2zoF1BgQhr2XsnE7q+3pf9BKpKdy/FeC8MMhrzPbE6+IQxXSZdv9bW6Bc+fY22mfPevY82pRnN2Ij/109cFfWPXPMx236sXZuHff4MwcpCUfQK5gFt8x9f/cQ+rTEg+j8ff5ne8TAzEV9zxK4jom8Xt9f42swc907oxjHbJR7ABjMGWs2inn3GgBEdrYJygHLpS3NqnViXYNPKJpKrYxfXuXPRdVtB7k6JVlokEEcXOwkupfEQdVJ8jrGC++nbbhGN03IvuWQrDa+s0ZYyUmvmIJhWzCsW2q8NEbvXTZ/WNzLaZaG4sDUSphmzpO+YZtlmaZZlZMMlbbS2LyHb8Ol8QbcOTtnserrI13o70wx9Bw5Yax8eHtNbH9unRb0uNMW9v/bJfRbqAV9/aT0DHR3wPKP3Q/bytKa7N2/S+y5til3AdiM3S6LPXL1JX/PIpmSTPs1q46xcSN176jWIgfrzDeS/c3SeSJijcrq4OZTFEWvDnP7017xVVA7U9kI2Rq4lLAyCvvnitiDkyxsDiSSKikSvQvQmnJYs6bUumwoVtKQdyLN5yVISYvgqudFTIIp6fTU6AMLL3nvol181ulunyTn6HoAweI0NLqSFa2SrEB/oCCqhgQBQvS6Qweshu2qyEIO/fcqarWoUH6BCeKPfozVx4dKYGodP32O1jP0EFXt66ScQtnRLbRueMT8v7D+I7hJtOrnGLieE7mZ7SE/ub9LlnQ3a5XkU7cGa4vjkjKX/VMD6V1zcoKsnc+n7+JusVUDfS4NMwu1bbKavT0rKTvgG77qoIAKJjFJamtyn917akIwRVO4or2NjiAwpRp40EH+ncPTQqKB9VjUXWLo3L+xQgSZIsnuWEwm4w/bpgNURcuXoky89AZmwO+zigMhFlkQA5phA2D8PExUDN55irx2AxylMTtvtEFp7v+LqhcNFhoBU4h64V2l7Hmlgi5+BmRZ2F/GCBQNQ8XCiuxduH21F9CiCqZBCDSYi+vHhA0jU0J7fOWuomen+ijh03QUyoAVd2VmXBp2n7O6dzXVdJFrJhbWUlSWKcD+0mWmMeeT8vnQup49dPaCETTYwAhZ+aCMPkvmt0We40l3MwJQNE/2Fwxk93zTCLJv8/SljgP8HHAIbP6ImDlMAAAAASUVORK5CYII=');
            background-size: 1680px auto;
            image-rendering: pixelated;
            image-rendering: crisp-edges;
            background-repeat: no-repeat;
            background-position: center center;
            background-color: var(--orange);
        }

        .container {
            display: flex;
            align-items: flex-end;
            justify-content: center;
            gap: 8px;
        }

        .top-aligned {
            align-self: flex-start;
        }

        canvas {
            width: 626px;
            height: 626px;
            background-color: var(--sage);
            border: 4px solid var(--graphite);
            box-shadow: 0 0 5px var(--charcoal);
            touch-action: none;
            user-select: none;
            -webkit-user-select: none;
        }

        .control-panel {
            display: flex;
            flex-direction: column;
            gap: 16px;
            margin-top: 0;
            margin-left: 60px;
        }

        .button-creative {
            background-color: var(--brick);
            color: var(--silver);
            border: 2px solid var(--graphite);
            padding: 16px 10px;
            font-size: 23px;
            font-weight: bold;
            cursor: pointer;
            transition: all 0.2s ease-in-out;
            border-radius: 4px;
            box-shadow: 3px 3px 0 var(--ebony);
            width: 190px;
            text-align: center;
            font-family: 'Courier New', Courier, monospace;
        }

        .button-creative:hover {
            background-color: var(--tan);
            color: var(--ebony);
            transform: scale(1.05);
        }

        input[type="file"],
        input[type="text"] {
            background-color: var(--tan);
            color: var(--ebony);
            border: 2px solid var(--graphite);
            padding: 4px;
            font-size: 14px;
            border-radius: 4px;
            width: 100px;
        }

        #color {
            width: 100px;
            box-sizing: border-box;
        }

        .color-picker {
            width: 120px;
            height: 100px;
            border-radius: 50%;
            border: 3px solid var(--graphite);
            background-color: var(--brick);
            text-align: center;
            font-size: 20px;
            font-weight: bold;
            cursor: pointer;
            box-shadow: 2px 2px 0 var(--ebony);
            font-family: 'Courier New', Courier, monospace;
            padding: 0;
            line-height: 60px;
            margin-left: 48px;
            margin-bottom: 34px;
        }

        #infoBox {
            display: none;
            position: fixed;
            top: 20%;
            left: 50%;
            transform: translateX(-50%);
            background-color: var(--sage);
            color: var(--ebony);
            border: 2px solid var(--graphite);
            padding: 20px;
            box-shadow: 4px 4px 0 var(--ebony);
            font-family: 'Courier New', Courier, monospace;
            font-size: 18px;
            font-weight: bold;
            border-radius: 6px;
            max-width: 700px;
            text-align: center;
            z-index: 1000;
        }
    </style>
</head>

<body>
    <div class="container">
        <canvas id="pixelCanvas"></canvas>
        <div class="control-panel">
            <input value="ffffff" data-jscolor="{preset:'dark'}" id="color" class="color-picker">
            <button class="button-creative" id="uploadButton">📩 Upload</button>
            <input type="file" id="fileInput" accept="image/*" style="display: none;" />
            <button class="button-creative" id="clearButton">🧼 Clear</button>
            <button class="button-creative" id="infoButton">📝 Info</button>
        </div>
        <div id="infoBox">
            <p>📺 Welcome to the UI of your own mini retro pixel screen!📺<br>
                🎨 Use color-picker to choose your desired color and start drawing on the canvas <br>
                📩 You can Upload a picture from your device by pressing "Upload" button or "Paste" (Ctrl-V) an image
                you have in clipboard to send it. (Make sure that the picture is close to the 1:1 ratio to avoid
                distortion)<br>
                🧼 "Clear" button lets you start from scratch!</p>
        </div>
    </div>

    <script>
        const canvas = document.getElementById('pixelCanvas');
        const ctx = canvas.getContext('2d');
        const colorPicker = document.getElementById('color');
        const ipAddress = "%%IP%%";
        const cols = 43;
        const rows = 43;
        const pixelSize = 14.4;

        canvas.width = cols * pixelSize;
        canvas.height = rows * pixelSize;

        let isDrawing = false;
        let history = [];
        const maxHistorySize = 10;
        let drawBuffer = [];
        let lastX = -1, lastY = -1;

        function saveState() {
            if (history.length >= maxHistorySize) history.shift();
            history.push(ctx.getImageData(0, 0, canvas.width, canvas.height));
        }


        function clearCanvas() {
            ctx.clearRect(0, 0, canvas.width, canvas.height);
            initializeGrid();
            history = [];
            fetch(`http://${ipAddress}/clear`);
        }

        function initializeGrid() {
            ctx.fillStyle = "#0d0602";
            ctx.fillRect(0, 0, canvas.width, canvas.height);
            drawGrid();
        }

        function drawGrid() {
            ctx.strokeStyle = "#030b15";
            ctx.lineWidth = 1;
            for (let y = 0; y <= rows; y++) {
                ctx.beginPath();
                ctx.moveTo(0, y * pixelSize);
                ctx.lineTo(canvas.width, y * pixelSize);
                ctx.stroke();
            }
            for (let x = 0; x <= cols; x++) {
                ctx.beginPath();
                ctx.moveTo(x * pixelSize, 0);
                ctx.lineTo(x * pixelSize, canvas.height);
                ctx.stroke();
            }
        }

        function getMousePos(event) {
            const rect = canvas.getBoundingClientRect();
            return {
                x: Math.floor((event.clientX - rect.left) / pixelSize),
                y: Math.floor((event.clientY - rect.top) / pixelSize)
            };
        }

        function hexToRGB(hex) {
            return {
                r: parseInt(hex.substring(1, 3), 16),
                g: parseInt(hex.substring(3, 5), 16),
                b: parseInt(hex.substring(5, 7), 16)
            };
        }

        function drawPixel(event) {
            const { x, y } = getMousePos(event);
            if (x !== lastX || y !== lastY) {
                const { r, g, b } = hexToRGB(colorPicker.value);
                ctx.fillStyle = `rgb(${r},${g},${b})`;
                ctx.fillRect(x * pixelSize, y * pixelSize, pixelSize, pixelSize);
                drawGrid();
                drawBuffer.push({ x, y, r, g, b });
                lastX = x;
                lastY = y;
            }
        }

        function sendDrawBuffer() {
            if (drawBuffer.length === 0) return;
            fetch(`http://${ipAddress}/batchDraw`, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify(drawBuffer)
            }).catch(console.error);
            drawBuffer = [];
        }


        // Unified pointer handlers (mouse, touch, pen)
        canvas.addEventListener('pointerdown', e => {
            // ignore non-left buttons on mouse
            if (e.button !== undefined && e.button !== 0) return;
            canvas.setPointerCapture?.(e.pointerId);
            saveState();
            isDrawing = true;
            drawPixel(e);              // your existing drawPixel can read e.clientX/Y
        }, { passive: false });

        canvas.addEventListener('pointermove', e => {
            if (!isDrawing) return;
            drawPixel(e);
        }, { passive: false });

        const endStroke = e => {
            if (!isDrawing) return;
            isDrawing = false;
            canvas.releasePointerCapture?.(e.pointerId);
            sendDrawBuffer();
        };

        canvas.addEventListener('pointerup', endStroke);
        canvas.addEventListener('pointercancel', endStroke);
        canvas.addEventListener('pointerleave', endStroke);

        // Optional: prevent long-press context menu on mobile
        canvas.addEventListener('contextmenu', e => e.preventDefault());



        document.getElementById('clearButton').addEventListener('click', clearCanvas);

        function pixelateImage(file) {
            const img = new Image();
            const reader = new FileReader();

            reader.onload = e => {
                img.onload = () => {
                    ctx.clearRect(0, 0, canvas.width, canvas.height);
                    const canvasAspect = canvas.width / canvas.height;
                    const imgAspect = img.width / img.height;
                    let drawWidth, drawHeight;

                    if (imgAspect > canvasAspect) {
                        drawWidth = canvas.width;
                        drawHeight = canvas.width / imgAspect;
                    } else {
                        drawWidth = canvas.height * imgAspect;
                        drawHeight = canvas.height;
                    }

                    ctx.drawImage(img, 0, 0, drawWidth, drawHeight);
                    const imageData = ctx.getImageData(0, 0, drawWidth, drawHeight);
                    const rowsPixels = Array.from({ length: rows }, () => []);

                    for (let y = 0; y < rows; y++) {
                        for (let x = 0; x < cols; x++) {
                            const px = Math.floor((x / cols) * drawWidth);
                            const py = Math.floor((y / rows) * drawHeight);
                            const idx = (py * drawWidth + px) * 4;
                            const r = imageData.data[idx],
                                g = imageData.data[idx + 1],
                                b = imageData.data[idx + 2];

                            ctx.fillStyle = `rgb(${r},${g},${b})`;
                            ctx.fillRect(x * pixelSize, y * pixelSize, pixelSize, pixelSize);
                            rowsPixels[y].push({ x, y, r, g, b });
                        }
                    }

                    drawGrid();
                    sendRowsSequentially(rowsPixels, 0);
                };
                img.src = e.target.result;
            };
            reader.readAsDataURL(file);
        }

        function sendRowsSequentially(rowsPixels, i) {
            if (i >= rowsPixels.length) return;
            fetch(`http://${ipAddress}/batchDraw`, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify(rowsPixels[i])
            })
                .then(() => sendRowsSequentially(rowsPixels, i + 1))
                .catch(console.error);
        }

        document.getElementById('uploadButton').addEventListener('click', () => {
            document.getElementById('fileInput').click();
        });

        document.getElementById('fileInput').addEventListener('change', e => {
            const file = e.target.files[0];
            if (file) pixelateImage(file);
        });

        // Paste listener to detect images from clipboard
        document.addEventListener('paste', event => {
            const items = event.clipboardData.items;
            for (let i = 0; i < items.length; i++) {
                const item = items[i];
                if (item.type.indexOf('image') !== -1) {
                    const file = item.getAsFile();
                    if (file) {
                        pixelateImage(file);
                        event.preventDefault();
                        break;
                    }
                }
            }
        });

        const infoButton = document.getElementById('infoButton');
        const infoBox = document.getElementById('infoBox');

        infoButton.addEventListener('click', () => {
            if (infoBox.style.display === 'block') {
                infoBox.style.display = 'none';
            } else {
                infoBox.style.display = 'block';
            }
        });


        initializeGrid();
    </script>
</body>

</html>
)rawliteral";
